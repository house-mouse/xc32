
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_javax_crypto_cipher_TripleDES__
#define __gnu_javax_crypto_cipher_TripleDES__

#pragma interface

#include <gnu/javax/crypto/cipher/BaseCipher.h>
#include <gcj/array.h>

extern "Java"
{
  namespace gnu
  {
    namespace javax
    {
      namespace crypto
      {
        namespace cipher
        {
            class DES;
            class TripleDES;
        }
      }
    }
  }
}

class gnu::javax::crypto::cipher::TripleDES : public ::gnu::javax::crypto::cipher::BaseCipher
{

public:
  TripleDES();
  static void adjustParity(JArray< jbyte > *, jint);
  static void adjustParity(jint, JArray< jbyte > *, jint);
  static jboolean isParityAdjusted(JArray< jbyte > *, jint);
  static jboolean isParityAdjusted(jint, JArray< jbyte > *, jint);
  virtual ::java::lang::Object * clone();
  virtual ::java::util::Iterator * blockSizes();
  virtual ::java::util::Iterator * keySizes();
  virtual ::java::lang::Object * makeKey(JArray< jbyte > *, jint);
  virtual void encrypt(JArray< jbyte > *, jint, JArray< jbyte > *, jint, ::java::lang::Object *, jint);
  virtual void decrypt(JArray< jbyte > *, jint, JArray< jbyte > *, jint, ::java::lang::Object *, jint);
  static const jint BLOCK_SIZE = 8;
  static const jint KEY_SIZE = 24;
private:
  ::gnu::javax::crypto::cipher::DES * __attribute__((aligned(__alignof__( ::gnu::javax::crypto::cipher::BaseCipher)))) des;
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_javax_crypto_cipher_TripleDES__
