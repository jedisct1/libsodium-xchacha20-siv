# XChaCha20-SIV

Deterministic/nonce-reuse resistant authenticated encryption scheme using XChaCha20, implemented on libsodium.

|                    | XChaCha20-Poly1305  | XChaCha20-SIV               |
| ------------------ | ------------------- | --------------------------- |
| Key size           | 256 bits            | 256 bits (before expansion) |
| Authentication tag | 128 bits            | 256 bits                    |
| Nonce size         | 192 bits, mandatory | 128 bits, optional          |
| Nonce reuse        | Can leak plaintext  | Leaks message duplication   |
| Speed              | Fast                | Not as fast                 |

## Usage

```c
int crypto_aead_det_xchacha20_encrypt_detached(
    unsigned char *c, unsigned char mac[crypto_aead_det_xchacha20_MACBYTES], const unsigned char *m,
    size_t mlen, const unsigned char *ad, size_t adlen, const unsigned char *nonce,
    const unsigned char k[crypto_aead_det_xchacha20_KEYBYTES]);
```

Encrypt a message `m` of length `mlen` bytes using a key `k`, an optional nonce `nonce` (which can left to `NULL`), optionally authenticating additional data `ad` (if not `NULL`) of length `adlen` bytes in addition to the message itself. The IV acting as a MAC is stored into `mac`.

```c
int crypto_aead_det_xchacha20_decrypt_detached(
    unsigned char *m, const unsigned char *c, unsigned long long clen,
    const unsigned char mac[crypto_aead_det_xchacha20_MACBYTES], const unsigned char *ad,
    unsigned long long adlen, const unsigned char *nonce,
    const unsigned char k[crypto_aead_det_xchacha20_KEYBYTES]);
```

Decrypt a ciphertext `c` or length `clen` bytes using a key `k`, an optional nonoce `nonce` (which can be left to `NULL`), optionally verifying additional data `ad` (if not `NULL`) of length `adlen` bytes in addition to the message itself, using the MAC `mac`.

The function returns `-1` if the authentication tag didn't verify, and `0` on success, storing the decrypted message into `m`.

```c
int crypto_aead_det_xchacha20_encrypt(unsigned char *c, const unsigned char *m, size_t mlen,
                                      const unsigned char *ad, size_t adlen,
                                      const unsigned char *nonce,
                                      const unsigned char  k[crypto_aead_det_xchacha20_KEYBYTES]);
```

Similar to `encrypt_detached`, but the ciphertext and MAC are concatenated.

`c` must be `mlen + crypto_aead_det_xchacha20_MACBYTES` long.

```c
int crypto_aead_det_xchacha20_decrypt(unsigned char *m, const unsigned char *c,
                                      unsigned long long clen, const unsigned char *ad,
                                      unsigned long long adlen, const unsigned char *nonce,
                                      const unsigned char k[crypto_aead_det_xchacha20_KEYBYTES]);
```

Similar to `decrypt_detached`, with the ciphertext and the MAC having been concatenated.

```c
void crypto_aead_det_xchacha20_keygen(unsigned char k[crypto_aead_det_xchacha20_KEYBYTES]);
```

Create a 256-bit secret key.
