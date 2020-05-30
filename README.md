# XChaCha20-SIV AEAD

Deterministic authenticated encryption using libsodium.

|                    | XChaCha20-Poly1305  | XChaCha20-SIV             |
| ------------------ | ------------------- | ------------------------- |
| Key size           | 256 bits            | 256 bits                  |
| Authentication tag | 128 bits            | 256 bits                  |
| Nonce size         | 192 bits, mandatory | 128 bits, optional        |
| Nonce reuse        | Can leak plaintext  | Leaks message duplication |
| Speed              | Fast                | Not as fast               |