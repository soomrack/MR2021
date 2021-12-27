#include "library.h"

int main() {
    Matrix A (4,4);
    {
        A.create(0, 0, 1);
        A.create(0, 1, 2);
        A.create(0, 2, 3);
        A.create(0, 3, 4);

        A.create(1, 0, 5);
        A.create(1, 1, 6);
        A.create(1, 2, 7);
        A.create(1, 3, 8);

        A.create(2, 0, 9);
        A.create(2, 1, 10);
        A.create(2, 2, 11);
        A.create(2, 3, 12);

        A.create(3, 0, 13);
        A.create(3, 1, 14);
        A.create(3, 2, 15);
        A.create(3, 3, 16);
    }
    Matrix B (4,4);
    {
        B.create(0, 0, 1);
        B.create(0, 1, 1);
        B.create(0, 2, 1);
        B.create(0, 3, 1);

        B.create(1, 0, 2);
        B.create(1, 1, 2);
        B.create(1, 2, 2);
        B.create(1, 3, 2);

        B.create(2, 0, 3);
        B.create(2, 1, 3);
        B.create(2, 2, 3);
        B.create(2, 3, 3);

        B.create(3, 0, 4);
        B.create(3, 1, 4);
        B.create(3, 2, 4);
        B.create(3, 3, 4);
    }

    A.print();//
    printf(" traceA=%.5lf\n",A.trace());
    B.print();//
    printf(" traceB=%.5lf\n",B.trace());

    Matrix C(4,4);
    Matrix D(4,4);
    Matrix E(4,4);
    Matrix F(4,4);
    D.gq_matrix();
    E.unit_matrix();
    F.zero_matrix();

    printf("\n C,D,E,F\n");//
    D.print();//
    printf("trace D=%.5lf\n",D.trace());
    E.print();//
    printf("trace E=%.5lf\n",E.trace());
    F.print();//
    printf("trace F=%.5lf\n",F.trace());

    C = D + E;
    printf("\n C=D+E\n");
    C.print();//

    C = E - D;
    printf("\n C=E-D\n");
    C.print();//

    C = D * E;
    printf("\n C=D*E\n");
    C.print();

    return 0;
}