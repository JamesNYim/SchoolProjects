#include <stdio.h>
#include <gmp.h>
#include "randstate.h"
#include "numtheoryinC.h"
#include "numtheory.h"
#include <inttypes.h>
#include "rsa.h"
#include <stdlib.h>
#include <time.h>

int main(void) {
    //initalizing test variables
    mpz_t x;
    mpz_t y;
    mpz_t v;
    mpz_init_set_ui(v, 12);
    mpz_init_set_ui(x, 32);
    mpz_init_set_ui(y, 256);

    uint64_t iters = 256;
    uint64_t bits = 24;

    //gcd
    mpz_t gcdInGMP;
    mpz_init(gcdInGMP);
    int32_t gcdInC = gcd_c(0, 310, 5);
    gcd(gcdInGMP, x, y);
    printf("gcdInC = %d \n", gcdInC);
    gmp_printf("gcdInGMP = %Zd \n", gcdInGMP);
    printf("\n");

    //mod inverse
    mpz_t modInverseInGMP;
    mpz_init(modInverseInGMP);
    int32_t modInverseInC = mod_inverse_c(0, 310, 5);
    mod_inverse(modInverseInGMP, x, y);
    printf("modInverseInC = %d \n", modInverseInC);
    gmp_printf("modInverseInGMP = %Zd \n", modInverseInGMP);
    printf("\n");

    //mod inverse
    mpz_t powModInGMP;
    mpz_init(powModInGMP);
    int32_t powModInC = pow_mod_c(0, 310, 5, 12);
    pow_mod(powModInGMP, x, y, v);
    printf("powModInC = %d \n", powModInC);
    gmp_printf("powModInGMP = %Zd \n", powModInGMP);
    printf("\n");

    //is_prime
    randstate_init(594607);
    if (is_prime_c(7, 50)) {
        printf("isPrimeInC = true \n");
    } else {
        printf("isPrimeInC = false \n");
    }
    if (is_prime(y, 50)) {
        printf("isPrimeInGMP = true \n");
    } else {
        printf("isPrimeInGMP = false \n");
    }
    randstate_clear();
    printf("\n");

    //make_prime
    randstate_init(time(0));
    srandom(time(0));
    int32_t primeNumInC = make_prime_c(0, 8, 256);

    mpz_t primeNumInGMP;
    mpz_init(primeNumInGMP);
    make_prime(primeNumInGMP, bits, iters);

    gmp_printf("primeNumInGMP = %Zd \n", primeNumInGMP);
    if (is_prime_c(primeNumInC, 50)) {
        printf("primeNumInC = true \n");
    } else {
        printf("primeNumInC = false \n");
    }

    printf("primeNumInC = %d \n", primeNumInC);
    if (is_prime(primeNumInGMP, 50)) {
        printf("primeNumInGMP = true \n");
    } else {
        printf("primeNumInGMP = false \n");
    }
    randstate_clear();
    printf("\n");

    //rsa_make_pub
    mpz_t p, q, n, e;
    mpz_inits(p, q, n, e, NULL);
    randstate_init(time(0));
    srandom(time(0));
    mpz_inits(p, q, n, e, NULL);
    rsa_make_pub(p, q, n, e, bits, iters);

    //write pub
    mpz_t s;
    mpz_init_set_ui(s, 102213123124);
    FILE *pbfile = fopen("pbfile", "w+");
    rsa_write_pub(n, e, s, "username", pbfile);
    gmp_printf("n = %Zd \n", n);
    gmp_printf("e = %Zd \n", e);
    gmp_printf("s = %Zd \n", s);

    //make priv
    mpz_t d;
    mpz_init(d);
    rsa_make_priv(d, e, p, q);

    //write priv
    FILE *pvfile = fopen("pvfile", "w+");
    rsa_write_priv(n, d, pvfile);

    //encrypt_file
    FILE *originalFile = fopen("originalFile", "r");
    FILE *encryptedFile = fopen("encryptedFile", "w");
    rsa_encrypt_file(originalFile, encryptedFile, n, e);
    fclose(originalFile);
    fclose(encryptedFile);

    encryptedFile = fopen("encryptedFile", "r");
    FILE *decryptedFile = fopen("decryptedFile", "w");
    rsa_decrypt_file(encryptedFile, decryptedFile, n, d);
    fclose(encryptedFile);

    fclose(decryptedFile);
    mpz_clears(p, q, n, e, d, NULL);
}
