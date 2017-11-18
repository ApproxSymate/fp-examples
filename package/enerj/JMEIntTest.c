/*
 * Portions Copyright 2017 National University of Singapore
 *
 * The C version of the jmeint Java code of benchmark.
 *
 * Below is the license information of the original Java program.
 */

/*
 * Copyright (c) 2003-2009 jMonkeyEngine
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of 'jMonkeyEngine' nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <klee/klee.h>

struct Vector3f {
  float x;
  float y;
  float z;
};

struct Vector2f {
  float x;
  float y;
};

/**
 * EPSILON represents the error buffer used to denote a hit.
 */
double EPSILON = 1e-12;

/* Approx */ struct Vector3f *tempVa;
/* Approx */ struct Vector3f *tempVb;
/* Approx */ struct Vector3f *tempVc;
/* Approx */ struct Vector3f *tempVd;
/* Approx */ struct Vector3f *tempVe;

/* Approx */ float tempFa[2];
/* Approx */ float tempFb[2];

/* Approx */ struct Vector2f *tempV2a;
/* Approx */ struct Vector2f *tempV2b;

int abs(int value) {
  if (value < 0)
    return -value;
  return value;
}

void subtract(struct Vector3f *v1, struct Vector3f *v2,
              struct Vector3f *result) {
  if (result == NULL)
    result = malloc(sizeof(struct Vector3f));
  result->x = v1->x - v2->x;
  result->y = v1->y - v2->y;
  result->z = v1->z - v2->z;
}

struct Vector3f *cross(struct Vector3f *v, float otherX, float otherY,
                       float otherZ, struct Vector3f *result) {
  if (result == NULL)
    result = malloc(sizeof(struct Vector3f));
  float resX = ((v->y * otherZ) - (v->z * otherY));
  float resY = ((v->z * otherX) - (v->x * otherZ));
  float resZ = ((v->x * otherY) - (v->y * otherX));
  result->x = resX;
  result->y = resY;
  result->z = resZ;
  return result;
}

float dot(struct Vector3f *v0, struct Vector3f *vec) {
  if (vec == NULL) {
    fprintf(stderr, "Provided vector is null, 0 returned.\n");
    return 0;
  }
  return v0->x * vec->x + v0->y * vec->y + v0->z * vec->z;
}

void sort(/* Approx */ float *f) {
  if ((f[0] > f[1])) {
    /* Approx */ float c = f[0];
    f[0] = f[1];
    f[1] = c;
  }
}

/* Approx */
int edgeEdgeTest(/* Approx */
                 float *v0,
                 /* Approx */
                 float *u0,
                 /* Approx */
                 float *u1, int i0, int i1,
                 /* Approx */
                 float aX,
                 /* Approx */
                 float Ay) {
  /* Approx */ float Bx = u0[i0] - u1[i0];
  /* Approx */ float By = u0[i1] - u1[i1];
  /* Approx */ float Cx = v0[i0] - u0[i0];
  /* Approx */ float Cy = v0[i1] - u0[i1];
  /* Approx */ float f = Ay * Bx - aX * By;
  /* Approx */ float d = By * Cx - Bx * Cy;
  if (((f > 0 && d >= 0 && d <= f) || (f < 0 && d <= 0 && d >= f))) {
    /* Approx */ float e = aX * Cy - Ay * Cx;
    if ((f > 0)) {
      if ((e >= 0 && e <= f))
        return 1;
    } else {
      if ((e <= 0 && e >= f))
        return 1;
    }
  }
  return 0;
}

/* Approx */
int pointInTri(/* Approx */ float *V0,
               /* Approx */ float *U0,
               /* Approx */ float *U1,
               /* Approx */ float *U2, int i0, int i1) {
  /* Approx */ float a, b, c, d0, d1, d2;
  /* is T1 completly inside T2? */
  /* check if V0 is inside tri(U0,U1,U2) */
  a = U1[i1] - U0[i1];
  b = -(U1[i0] - U0[i0]);
  c = -a * U0[i0] - b * U0[i1];
  d0 = a * V0[i0] + b * V0[i1] + c;

  a = U2[i1] - U1[i1];
  b = -(U2[i0] - U1[i0]);
  c = -a * U1[i0] - b * U1[i1];
  d1 = a * V0[i0] + b * V0[i1] + c;

  a = U0[i1] - U2[i1];
  b = -(U0[i0] - U2[i0]);
  c = -a * U2[i0] - b * U2[i1];
  d2 = a * V0[i0] + b * V0[i1] + c;
  if ((d0 * d1 > 0.0 && d0 * d2 > 0.0))
    return 1;

  return 0;
}

/* Approx */ int edgeAgainstTriEdges(/* Approx */ float *v0,
                                     /* Approx */ float *v1,
                                     /* Approx */ float *u0,
                                     /* Approx */ float *u1,
                                     /* Approx */ float *u2, int i0, int i1) {
  /* Approx */ float aX, aY;
  aX = v1[i0] - v0[i0];
  aY = v1[i1] - v0[i1];
  /* test edge u0,u1 against v0,v1 */
  if ((edgeEdgeTest(v0, u0, u1, i0, i1, aX, aY))) {
    return 1;
  }
  /* test edge u1,u2 against v0,v1 */
  if ((edgeEdgeTest(v0, u1, u2, i0, i1, aX, aY))) {
    return 1;
  }
  /* test edge u2,u1 against v0,v1 */
  if ((edgeEdgeTest(v0, u2, u0, i0, i1, aX, aY))) {
    return 1;
  }
  return 0;
}

int newComputeIntervals(
    /* Approx */ float vv0,
    /* Approx */ float vv1,
    /* Approx */ float vv2,
    /* Approx */ float d0,
    /* Approx */ float d1,
    /* Approx */ float d2,
    /* Approx */ float d0d1,
    /* Approx */ float d0d2,
    /* Approx */ struct Vector3f *abc,
    /* Approx */ struct Vector2f *x0x1) {
  if ((d0d1 > 0.0f)) {
    /* here we know that d0d2 <=0.0 */
    /*
     * that is d0, d1 are on the same side, d2 on the other or on the
     * plane
     */
    abc->x = vv2;
    abc->y = (vv0 - vv2) * d2;
    abc->z = (vv1 - vv2) * d2;
    x0x1->x = d2 - d0;
    x0x1->y = d2 - d1;
  } else if ((d0d2 > 0.0f)) {
    /* here we know that d0d1 <=0.0 */
    abc->x = vv1;
    abc->y = (vv0 - vv1) * d1;
    abc->z = (vv2 - vv1) * d1;
    x0x1->x = d1 - d0;
    x0x1->y = d1 - d2;
  } else if ((d1 * d2 > 0.0f || d0 != 0.0f)) {
    /* here we know that d0d1 <=0.0 or that d0!=0.0 */
    abc->x = vv0;
    abc->y = (vv1 - vv0) * d0;
    abc->z = (vv2 - vv0) * d0;
    x0x1->x = d0 - d1;
    x0x1->y = d0 - d2;
  } else if ((d1 != 0.0f)) {
    abc->x = vv1;
    abc->y = (vv0 - vv1) * d1;
    abc->z = (vv2 - vv1) * d1;
    x0x1->x = d1 - d0;
    x0x1->y = d1 - d2;
  } else if ((d2 != 0.0f)) {
    abc->x = vv2;
    abc->y = (vv0 - vv2) * d2;
    abc->z = (vv1 - vv2) * d2;
    x0x1->x = d2 - d0;
    x0x1->y = d2 - d1;
  } else {
    /* triangles are coplanar */
    return 1;
  }
  return 0;
}

/* Approx */
int coplanarTriTri(/* Approx */ struct Vector3f *n,
                   /* Approx */ struct Vector3f *v0,
                   /* Approx */ struct Vector3f *v1,
                   /* Approx */ struct Vector3f *v2,
                   /* Approx */ struct Vector3f *u0,
                   /* Approx */ struct Vector3f *u1,
                   /* Approx */ struct Vector3f *u2) {
  /* Approx */ struct Vector3f a;
  short i0, i1;
  a.x = abs(n->x);
  a.y = abs(n->y);
  a.z = abs(n->z);

  if ((a.x > a.y)) {
    if ((a.x > a.z)) {
      i0 = 1; /* a[0] is greatest */
      i1 = 2;
    } else {
      i0 = 0; /* a[2] is greatest */
      i1 = 1;
    }
  } else /* a[0] <=a[1] */ {
    if ((a.z > a.y)) {
      i0 = 0; /* a[2] is greatest */
      i1 = 1;
    } else {
      i0 = 0; /* a[1] is greatest */
      i1 = 2;
    }
  }

  /* test all edges of triangle 1 against the edges of triangle 2 */
  /* Approx */ float v0f[3];
  v0f[0] = v0->x;
  v0f[1] = v0->y;
  v0f[2] = v0->z;
  /* Approx */ float v1f[3];
  v1f[0] = v1->x;
  v1f[0] = v1->y;
  v1f[0] = v1->z;
  /* Approx */ float v2f[3];
  v2f[0] = v2->x;
  v2f[0] = v2->y;
  v2f[0] = v2->z;
  /* Approx */ float u0f[3];
  u0f[0] = u0->x;
  u0f[0] = u0->y;
  u0f[0] = u0->z;
  /* Approx */ float u1f[3];
  u1f[0] = u1->x;
  u1f[0] = u1->y;
  u1f[0] = u1->z;
  /* Approx */ float u2f[3];
  u2f[0] = u2->x;
  u2f[0] = u2->y;
  u2f[0] = u2->z;
  if ((edgeAgainstTriEdges(v0f, v1f, u0f, u1f, u2f, i0, i1))) {
    return 1;
  }

  if ((edgeAgainstTriEdges(v1f, v2f, u0f, u1f, u2f, i0, i1))) {
    return 1;
  }

  if ((edgeAgainstTriEdges(v2f, v0f, u0f, u1f, u2f, i0, i1))) {
    return 1;
  }

  /* finally, test if tri1 is totally contained in tri2 or vice versa */
  pointInTri(v0f, u0f, u1f, u2f, i0, i1);
  pointInTri(u0f, v0f, v1f, v2f, i0, i1);

  return 0;
}

/**
 * This method tests for the intersection between two triangles defined by
 * their vertexes. Converted to java from C code found at
 * http://www.acm.org/jgt/papers/Moller97/tritri.html
 *
 * @param v0
 *            First triangle's first vertex.
 * @param v1
 *            First triangle's second vertex.
 * @param v2
 *            First triangle's third vertex.
 * @param u0
 *            Second triangle's first vertex.
 * @param u1
 *            Second triangle's second vertex.
 * @param u2
 *            Second triangle's third vertex.
 * @return True if the two triangles intersect, false otherwise.
 */
/* Approx */
int intersection(/* Approx */
                 struct Vector3f *v0,
                 /* Approx */
                 struct Vector3f *v1,
                 /* Approx */
                 struct Vector3f *v2,
                 /* Approx */
                 struct Vector3f *u0,
                 /* Approx */
                 struct Vector3f *u1,
                 /* Approx */
                 struct Vector3f *u2) {
  /* Approx */
  struct Vector3f *e1 = tempVa;
  /* Approx */
  struct Vector3f *e2 = tempVb;
  /* Approx */
  struct Vector3f *n1 = tempVc;
  /* Approx */
  struct Vector3f *n2 = tempVd;
  /* Approx */
  float d1, d2;
  /* Approx */
  float du0, du1, du2, dv0, dv1, dv2;
  /* Approx */
  struct Vector3f *d = tempVe;
  /* Approx */
  float *isect1 = tempFa;
  /* Approx */
  float *isect2 = tempFb;
  /* Approx */
  float du0du1, du0du2, dv0dv1, dv0dv2;
  short index;
  /* Approx */
  float vp0, vp1, vp2;
  /* Approx */
  float up0, up1, up2;
  /* Approx */
  float bb, cc, max;
  /* Approx */
  float xx, yy, xxyy, tmp;

  /* compute plane equation of triangle(v0,v1,v2) */
  subtract(v1, v0, e1);
  subtract(v2, v0, e2);
  cross(e1, e2->x, e2->y, e2->z, n1);
  d1 = -(dot(n1, v0));
  /* plane equation 1: n1.X+d1=0 */

  /*
   * put u0,u1,u2 into plane equation 1 to compute signed distances to the
   * plane
   */
  du0 = dot(n1, u0) + d1;
  du1 = dot(n1, u1) + d1;
  du2 = dot(n1, u2) + d1;

  /* coplanarity robustness check */
  if ((abs(du0) < EPSILON))
    du0 = 0.0f;
  if ((abs(du1) < EPSILON))
    du1 = 0.0f;
  if ((abs(du2) < EPSILON))
    du2 = 0.0f;
  du0du1 = du0 * du1;
  du0du2 = du0 * du2;

  if ((du0du1 > 0.0f && du0du2 > 0.0f)) {
    return 0;
  }

  /* compute plane of triangle (u0,u1,u2) */
  subtract(u1, u0, e1);
  subtract(u2, u0, e2);
  cross(e1, e2->x, e2->y, e2->z, n2);
  d2 = -(dot(n2, u0));
  /* plane equation 2: n2.X+d2=0 */

  /* put v0,v1,v2 into plane equation 2 */
  dv0 = dot(n2, v0) + d2;
  dv1 = dot(n2, v1) + d2;
  dv2 = dot(n2, v2) + d2;

  if ((abs(dv0) < EPSILON))
    dv0 = 0.0f;
  if ((abs(dv1) < EPSILON))
    dv1 = 0.0f;
  if ((abs(dv2) < EPSILON))
    dv2 = 0.0f;

  dv0dv1 = dv0 * dv1;
  dv0dv2 = dv0 * dv2;

  if ((dv0dv1 > 0.0f &&
       dv0dv2 > 0.0f)) { /*
                                              * same sign on all of them + not
                                              * equal 0 ?
                                              */
    return 0; /* no intersection occurs */
  }

  /* compute direction of intersection line */
  cross(n1, n2->x, n2->y, n2->z, d);

  /* compute and index to the largest component of d */
  max = abs(d->x);
  index = 0;
  bb = abs(d->y);
  cc = abs(d->z);
  if ((bb > max)) {
    max = bb;
    index = 1;
  }
  if ((cc > max)) {
    max = cc;
    vp0 = v0->z;
    vp1 = v1->z;
    vp2 = v2->z;

    up0 = u0->z;
    up1 = u1->z;
    up2 = u2->z;

  } else if (index == 1) {
    vp0 = v0->y;
    vp1 = v1->y;
    vp2 = v2->y;

    up0 = u0->y;
    up1 = u1->y;
    up2 = u2->y;
  } else {
    vp0 = v0->x;
    vp1 = v1->x;
    vp2 = v2->x;

    up0 = u0->x;
    up1 = u1->x;
    up2 = u2->x;
  }

  /* compute interval for triangle 1 */
  /* Approx */ struct Vector3f *abc = tempVa;
  /* Approx */ struct Vector2f *x0x1 = tempV2a;
  if (newComputeIntervals(vp0, vp1, vp2, dv0, dv1, dv2, dv0dv1, dv0dv2, abc,
                          x0x1)) {
    return coplanarTriTri(n1, v0, v1, v2, u0, u1, u2);
  }

  /* compute interval for triangle 2 */
  /* Approx */ struct Vector3f *def = tempVb;
  /* Approx */ struct Vector2f *y0y1 = tempV2b;
  if (newComputeIntervals(up0, up1, up2, du0, du1, du2, du0du1, du0du2, def,
                          y0y1)) {
    return coplanarTriTri(n1, v0, v1, v2, u0, u1, u2);
  }

  xx = x0x1->x * x0x1->y;
  yy = y0y1->x * y0y1->y;
  xxyy = xx * yy;

  tmp = abc->x * xxyy;
  isect1[0] = tmp + abc->y * x0x1->y * yy;
  isect1[1] = tmp + abc->z * x0x1->x * yy;

  tmp = def->x * xxyy;
  isect2[0] = tmp + def->y * xx * y0y1->y;
  isect2[1] = tmp + def->z * xx * y0y1->x;

  sort(isect1);
  sort(isect2);

  if ((isect1[1] < isect2[0] || isect2[1] < isect1[0])) {
    return 0;
  }

  return 1;
}

/* Approx */
struct Vector3f *randvec() {
  struct Vector3f *ret = malloc(sizeof(struct Vector3f));
  int a, b, c;

  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
  klee_make_symbolic(&c, sizeof(int), "c");

  ret->x = a;
  ret->y = b;
  ret->z = c;

  return ret;
}

int main(int argc, char **argv) {
  tempVa = /* Approx */ malloc(sizeof(struct Vector3f));
  tempVb = /* Approx */ malloc(sizeof(struct Vector3f));
  tempVc = /* Approx */ malloc(sizeof(struct Vector3f));
  tempVd = /* Approx */ malloc(sizeof(struct Vector3f));
  tempVe = /* Approx */ malloc(sizeof(struct Vector3f));
  tempV2a = /* Approx */ malloc(sizeof(struct Vector2f));
  tempV2b = /* Approx */ malloc(sizeof(struct Vector2f));

  // Use a constant seed so we operate deterministically.
  for (int i = 0; i <= 100; ++i) {
    struct Vector3f *v0 = randvec();
    struct Vector3f *v1 = randvec();
    struct Vector3f *v2 = randvec();
    struct Vector3f *v3 = randvec();
    struct Vector3f *v4 = randvec();
    struct Vector3f *v5 = randvec();

    /* Approx */
    int isec = intersection(v0, v1, v2, v3, v4, v5);
    if (isec) {
      printf("1 \n");
    } else {
      printf("0 \n");
    }

    free(v0);
    free(v1);
    free(v2);
    free(v3);
    free(v4);
    free(v5);
  }

  printf("\n");

  free(tempVa);
  free(tempVb);
  free(tempVc);
  free(tempVd);
  free(tempVe);
  free(tempV2a);
  free(tempV2b);

  return 0;
}
