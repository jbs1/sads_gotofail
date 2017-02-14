#include <iostream>
#include <string>
#include <cstdint>

using namespace std;
typedef int OSStatus;
typedef string SSLContext;
typedef int SSLBuffer;


struct SSLHashSHA1
{
	OSStatus update(string*, int*);
	OSStatus final (string*, string*);
};

OSStatus SSLHashSHA1::update(string* ctx, int* ran){
	return 0;
}

OSStatus SSLHashSHA1::final(string* ctx, string* out){
	return 0;
}

void SSLFreeBuffer(string* shash){
	cout << "freebuff:" << shash <<endl;
}



string signedHashes = "hashstuff";
string hashCtx = "hashsontext";

static OSStatus SSLVerifySignedServerKeyExchange(
	SSLContext *ctx, bool isRsa, SSLBuffer signedParams, uint8_t *signature, uint16_t signatureLen)
{
	OSStatus err;

	if ((err = SSLHashSHA1.update(&hashCtx, &serverRandom)) != 0)
		goto fail;
	if ((err = SSLHashSHA1.update(&hashCtx, &signedParams)) != 0)
		goto fail;
		goto fail;
	if ((err = SSLHashSHA1.final(&hashCtx, &hashOut)) != 0)
		goto fail;


	fail:
		SSLFreeBuffer(&signedHashes);
		SSLFreeBuffer(&hashCtx);
		return err;
}

int main(int argc, char const *argv[])
{
	SSLContext ctx = "bla";
	bool isrsa = true;
	SSLBuffer sigpar= 1234;
	uint8_t sig= 1234;
	uint16_t siglen= 5678;

	OSStatus result = SSLVerifySignedServerKeyExchange(&ctx,isrsa,sigpar,&sig,siglen);


	return 0;
}