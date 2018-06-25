package main // EncryptAes128Ecb encrypts the input with the given key using AES-128 in
import (
	"crypto/aes"
	"encoding/base64"
	"fmt"
	"log"
)

var ZeroIV = make([]byte, aes.BlockSize)

func Pkcs7Pad(input []byte, blockSize int) []byte {
	if blockSize <= 0 {
		panic("Block size must be positive")

	}
	// if the input is a whole number of blocks, it gets padded with an
	// extra block so there are always some padding bytes.
	padding_bytes := blockSize - len(input)%blockSize
	if padding_bytes > 0xff {
		panic("Padding bytes can't exceed 255")

	}
	for i := 0; i < padding_bytes; i++ {
		input = append(input, byte(padding_bytes))

	}
	return input

}
func Pkcs7Unpad(input []byte) []byte {
	if len(input) == 0 {
		panic("Empty string is not valid PKCS#7")

	}
	lastByte := int(input[len(input)-1])
	if lastByte > len(input) {
		panic(fmt.Sprintf("Malformed input: length %d with %d padding bytes",
			len(input), lastByte))

	}
	// make sure all the padding bytes match
	paddingStart := len(input) - lastByte
	for i := paddingStart; i < len(input)-1; i++ {
		if int(input[i]) != lastByte {
			panic(fmt.Sprintf("Malformed input: padding byte %d != %d",
				input[i], lastByte))

		}

	}
	return input[:paddingStart]

}

// ECB mode. No padding is used, so the input must be a whole number of blocks.
func EncryptAes128EcbWholeBlocks(input []byte, key []byte) []byte {
	// NewCipher will complain here if the key is too short
	block, err := aes.NewCipher(key)
	if err != nil {
		panic(err)
	}
	size := block.BlockSize()
	if len(input)%size != 0 {
		panic(fmt.Sprintf("Input length %d is not a multiple of block size %d",
			len(input), size))
	}
	output := []byte{}
	for i := 0; i < len(input); i += size {
		dst := make([]byte, size)
		block.Encrypt(dst, input[i:i+size])
		output = append(output, dst...)
		log.Println(len(dst))
	}
	return output
}
func EncryptAes128Ecb(input []byte, key []byte) []byte {
	input = Pkcs7Pad(input, aes.BlockSize)
	return EncryptAes128EcbWholeBlocks(input, key)

}

// DecryptAes128Ecb decrypts the input using the given key using AES-128 in
// ECB mode. (the standard library left out ECB mode because it's insecure.)
func DecryptAes128Ecb(input []byte, key []byte) []byte {
	if len(key) == 0 {
		panic("Key must not be empty")

	}
	block, err := aes.NewCipher(key)
	if err != nil {
		panic(err)

	}
	size := block.BlockSize()
	output := []byte{}
	for i := 0; i < len(input); i += size {
		dst := make([]byte, size)
		block.Decrypt(dst, input[i:i+size])
		output = append(output, dst...)

	}
	return output

}
func main() {
	key := []byte("12345678901234567890123456789012")
	out := EncryptAes128Ecb([]byte("111111111111111111"), key)
	fmt.Println(base64.StdEncoding.EncodeToString(out))

	os := ""
	os = "B+HuUVixIt9S2wq8XgAH9A=="
	os = "WqP0I8NvMyCSiOczou2R6w=="
	os = "qRSGZEjbvHv+3/ijuwG3zQ=="
	out, err := base64.StdEncoding.DecodeString(string(os))
	fmt.Println("length after decode:", len(out))

	decrypted := DecryptAes128Ecb(out, key)
	if err != nil {
		log.Println(err)

	}
	fmt.Printf("%s---", string(decrypted))

}
