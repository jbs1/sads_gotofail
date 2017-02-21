#include <iostream>
#include <string>
#include <cstdint>

using namespace std;
typedef int OSStatus;
typedef string SSLContext;
typedef int SSLBuffer;

//useless parameters
SSLContext ctx = "bla";
bool isrsa = true;
uint8_t sig= 12;
uint16_t siglen= 5678;
string signedHashes = "hashstuff";
string hashCtx = "hashsontext";


//testing parameters (init to all nonfail)
int serverRandom = 0; //nonzero == fail > gotofail for first sha1 methode
SSLBuffer sigpar= 0; //nonzero == fail > gotofail for second sha1 methode
string hashOut = "nonfail"; //"fail" == error condition > gotofail for third sha1 methode


//init result
OSStatus result = 0;



class SSLHashSHA1
{
	SSLHashSHA1();
	~SSLHashSHA1();
	public:
		static OSStatus update(string*, int*);
		static OSStatus final (string*, string*);
};

OSStatus SSLHashSHA1::update(string* ctx, int* ran){
	//cout << "--------" << *ran<<endl;
	return *ran;
}

OSStatus SSLHashSHA1::final(string* ctx, string* out){
	//cout << "--------" << *out<<endl;
	if ((*out).compare("fail")==0){
		return 1;
	} else {
		return 0;
	}
}

void SSLFreeBuffer(string* shash){
}



static OSStatus SSLVerifySignedServerKeyExchange(SSLContext *ctx, bool isRsa, SSLBuffer signedParams, uint8_t *signature, uint16_t signatureLen)
{
	OSStatus err=0;


	if ((err = SSLHashSHA1::update(&hashCtx, &serverRandom)) != 0)
		goto fail;
	if ((err = SSLHashSHA1::update(&hashCtx, &signedParams)) != 0)
		goto fail;
		goto fail;
	if ((err = SSLHashSHA1::final(&hashCtx, &hashOut)) != 0)
		goto fail;

	cout << "nonfail" << endl;

	fail:
		SSLFreeBuffer(&signedHashes);
		SSLFreeBuffer(&hashCtx);
		return err;
}

void unittest(){
	//all tests passing
	cout << "-----nonfail: result should be ZERO-----" << endl;
	cout<<SSLVerifySignedServerKeyExchange(&ctx,isrsa,sigpar,&sig,siglen)<<endl;


	//first test fail
	cout << "-----firstfail: result should be NONZERO-----" << endl;
	serverRandom = 1;
	cout << SSLVerifySignedServerKeyExchange(&ctx,isrsa,sigpar,&sig,siglen)<<endl;
	serverRandom = 0;

	//second test fail
	cout << "-----secondfail: result should be NONZERO-----" << endl;
	sigpar= 1;
	cout<<SSLVerifySignedServerKeyExchange(&ctx,isrsa,sigpar,&sig,siglen)<<endl;
	sigpar= 0;

	//third test fail
	cout << "-----thirdfail: result should be NONZERO-----" << endl;
	hashOut = "fail";
	cout<<SSLVerifySignedServerKeyExchange(&ctx,isrsa,sigpar,&sig,siglen)<<endl;
	hashOut = "nonfail";

}





int main(int argc, char const *argv[])
{

	//OSStatus result = SSLVerifySignedServerKeyExchange(&ctx,isrsa,sigpar,&sig,siglen);
	//cout << result <<endl;
	unittest();

	return 0;
}