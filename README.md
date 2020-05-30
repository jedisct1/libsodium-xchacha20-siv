# XChaCha20-SIV AEAD

Deterministic authenticated encryption using libsodium.

|                    | XChaCha20-Poly1305  | XChaCha20-SIV                  |
| ------------------ | ------------------- | ------------------------------ |
| Nonce size         | 192 bits, mandatory | 128 bits, optional             |
| Key size           | 256 bits            | 256 bits                       |
| Authentication tag | 128 bits            | 256 bits                       |
| Nonce reuse        | Catastrophic        | Only leaks message duplication |
| Speed              | Fast                | Not as fast                    |