#include <iostream>
#include <string>
#include <cstdint>

using namespace std;
typedef int OSStatus;
typedef string SSLContext;
typedef int SSLBuffer;


//testing parameters
int serverRandom = 0; //nonzero == fail > gotofail for first sha1 methode
SSLBuffer sigpar= 0; //nonzero == fail > gotofail for second sha1 methode
string hashOut = "fail"; //"fail" == error condition > gotofail for third sha1 methode


class SSLHashSHA1
{
	SSLHashSHA1();
	~SSLHashSHA1();
	public:
		static OSStatus update(string*, int*);
		static OSStatus final (string*, string*);
};

OSStatus SSLHashSHA1::update(string* ctx, int* ran){
	return *ran;
}

OSStatus SSLHashSHA1::final(string* ctx, string* out){
	if ((*out).compare("fail")==0){
		return 1;
	} else {
		return 0;
	}
}

void SSLFreeBuffer(string* shash){
}



string signedHashes = "hashstuff";
string hashCtx = "hashsontext";


static OSStatus SSLVerifySignedServerKeyExchange(
	SSLContext *ctx, bool isRsa, SSLBuffer signedParams, uint8_t *signature, uint16_t signatureLen)
{
	OSStatus err;

	if ((err = SSLHashSHA1::update(&hashCtx, &serverRandom)) != 0)
		goto fail;
	if ((err = SSLHashSHA1::update(&hashCtx, &signedParams)) != 0)
		goto fail;
		goto fail;
	if ((err = SSLHashSHA1::final(&hashCtx, &hashOut)) != 0)
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
	uint8_t sig= 12;
	uint16_t siglen= 5678;

	OSStatus result = SSLVerifySignedServerKeyExchange(&ctx,isrsa,sigpar,&sig,siglen);
	cout << result <<endl;


	return 0;
}