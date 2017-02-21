#include <iostream>
#include <string>
#include <cstdint>
#include <cstring>

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
		//goto fail;
	if ((err = SSLHashSHA1::final(&hashCtx, &hashOut)) != 0)
		goto fail;


	fail:
		SSLFreeBuffer(&signedHashes);
		SSLFreeBuffer(&hashCtx);
		return err;
}

bool unittest(){
	//all tests passing
	cout << "TESTING nonfail" << endl;
	result = SSLVerifySignedServerKeyExchange(&ctx,isrsa,sigpar,&sig,siglen);
	if(result != 0){
		cout << "FAIL!" << endl;
		return true;
	}


	//first test fail
	cout << "TESTING first fail" << endl;
	serverRandom = 1;
	result = SSLVerifySignedServerKeyExchange(&ctx,isrsa,sigpar,&sig,siglen);
	serverRandom = 0;
	if(result == 0){
		cout << "FAIL!" << endl;
		return true;
	}

	//second test fail
	cout << "TESTING second fail" << endl;
	sigpar = 1;
	result = SSLVerifySignedServerKeyExchange(&ctx,isrsa,sigpar,&sig,siglen);
	sigpar = 0;
	if(result == 0){
		cout << "FAIL!" << endl;
		return true;
	}

	//third test fail
	cout << "TESTING third fail" << endl;
	hashOut = "fail";
	result = SSLVerifySignedServerKeyExchange(&ctx,isrsa,sigpar,&sig,siglen);
	hashOut = "nonfail";
	if(result == 0){
		cout << "FAIL!" << endl;
		return true;
	}
	return false;

}





int main(int argc, char const *argv[])
{
	if (argc==2 && strcmp(argv[1],"testing")==0){
		return unittest();
	}

	//OSStatus result = SSLVerifySignedServerKeyExchange(&ctx,isrsa,sigpar,&sig,siglen);
	// cout << argc <<endl;



	return 0;
}