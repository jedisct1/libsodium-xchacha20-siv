all: test_xchacha20
	./test_xchacha20

test_xchacha20: test/test_xchacha20.c xchacha20-blake2b/crypto_aead_det_xchacha20.c xchacha20-blake2b/crypto_aead_det_xchacha20.h
	$(CC) -o test_xchacha20 test/test_xchacha20.c xchacha20-blake2b/crypto_aead_det_xchacha20.c -lsodium

clean:
	$(RM) test_xchacha20
