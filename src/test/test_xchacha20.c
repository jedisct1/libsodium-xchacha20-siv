#include "../xchacha20/crypto_aead_det_xchacha20.h"
#include <sodium.h>
#include <stdio.h>
#include <string.h>

int
main(void)
{
    unsigned char  k[crypto_aead_det_xchacha20_KEYBYTES];
    unsigned char *m, *m2, *c;
    unsigned char *nonce, *ad;
    size_t         mlen, clen, adlen;

    if (sodium_init() != 0) {
        return 1;
    }

    crypto_aead_det_xchacha20_keygen(k);
    mlen = randombytes_uniform(1000);
    clen = mlen + crypto_aead_det_xchacha20_MACBYTES;
    m    = sodium_malloc(mlen);
    m2   = sodium_malloc(mlen);
    c    = sodium_malloc(clen);

    randombytes_buf(m, mlen);

    printf("Testing without a nonce and without additional data... ");
    fflush(stdout);

    crypto_aead_det_xchacha20_encrypt(c, m, mlen, NULL, 0, NULL, k);
    if (crypto_aead_det_xchacha20_decrypt(m2, c, clen, NULL, 0, NULL, k) != 0) {
        puts("Verification failed");
        return 1;
    }
    if (memcmp(m2, m, mlen) != 0) {
        puts("Decrypted message doesn't match");
        return 1;
    }
    c[0]++;
    if (crypto_aead_det_xchacha20_decrypt(m2, c, clen, NULL, 0, NULL, k) == 0) {
        puts("Forgery not detected");
        return 1;
    }
    puts("Success!");

    printf("Testing with a nonce and additional data... ");
    fflush(stdout);

    nonce = sodium_malloc(crypto_aead_det_xchacha20_NONCEBYTES);
    randombytes_buf(nonce, crypto_aead_det_xchacha20_NONCEBYTES);

    adlen = randombytes_uniform(1000);
    ad    = sodium_malloc(adlen);
    randombytes_buf(ad, adlen);

    crypto_aead_det_xchacha20_encrypt(c, m, mlen, ad, adlen, nonce, k);
    if (crypto_aead_det_xchacha20_decrypt(m2, c, clen, ad, adlen, nonce, k) != 0) {
        puts("Verification failed");
        return 1;
    }
    if (memcmp(m2, m, mlen) != 0) {
        puts("Decrypted message doesn't match");
        return 1;
    }
    c[0]++;
    if (crypto_aead_det_xchacha20_decrypt(m2, c, clen, ad, adlen, nonce, k) == 0) {
        puts("Forgery not detected");
        return 1;
    }
    puts("Success!");

    sodium_free(ad);
    sodium_free(nonce);
    sodium_free(c);
    sodium_free(m2);
    sodium_free(m);

    return 0;
}
