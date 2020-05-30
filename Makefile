all: test1
	./test1

test1: test/test1.c src/xchacha20-blake2b/crypto_aead_det_xchacha20.c src/xchacha20-blake2b/crypto_aead_det_xchacha20.h
	$(CC) -o test1 test/test1.c src/xchacha20-blake2b/crypto_aead_det_xchacha20.c -lsodium

clean:
	$(RM) test1
