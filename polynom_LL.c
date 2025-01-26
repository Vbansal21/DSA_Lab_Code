#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    int coeff;
    int exp;
    struct Term* next;
} Term;

Term* createTerm(int coeff, int exp) {
    Term* newTerm = (Term*)malloc(sizeof(Term));
    newTerm->coeff = coeff; newTerm->exp = exp; newTerm->next = NULL;
    return newTerm;
}

Term* insertTerm(Term* poly, int coeff, int exp) {
    Term* newTerm = createTerm(coeff, exp);
    if(poly == NULL || exp > poly->exp) { newTerm->next = poly; poly = newTerm; }
    else {
        Term* current = poly;
        while(current->next != NULL && current->next->exp >= exp)
            current = current->next;
        if(current->exp == exp) { current->coeff += coeff; free(newTerm); }
        else { newTerm->next = current->next; current->next = newTerm; }
    }
    return poly;
}

void displayPolynomial(Term* poly) {
    if(poly == NULL) { printf("0\n"); return; }
    while(poly != NULL) { printf("%dx^%d", poly->coeff, poly->exp); poly = poly->next; if(poly != NULL && poly->coeff >=0) printf(" + "); else if(poly != NULL) printf(" "); }
    printf("\n");
}

Term* multiplyPolynomials(Term* poly1, Term* poly2) {
    Term* result = NULL;
    for(Term* p1 = poly1; p1 != NULL; p1 = p1->next)
        for(Term* p2 = poly2; p2 != NULL; p2 = p2->next)
            result = insertTerm(result, p1->coeff * p2->coeff, p1->exp + p2->exp);
    return result;
}

void freePolynomial(Term* poly) {
    while(poly != NULL) { Term* temp = poly; poly = poly->next; free(temp); }
}

int main() {
    Term* poly1 = NULL; Term* poly2 = NULL;
    poly1 = insertTerm(poly1, 3, 2); poly1 = insertTerm(poly1, 5, 1); poly1 = insertTerm(poly1, 6, 0);
    poly2 = insertTerm(poly2, 6, 1); poly2 = insertTerm(poly2, 8, 0);
    displayPolynomial(poly1); displayPolynomial(poly2);
    Term* product = multiplyPolynomials(poly1, poly2);
    displayPolynomial(product);
    freePolynomial(poly1); freePolynomial(poly2); freePolynomial(product);
    return 0;
}