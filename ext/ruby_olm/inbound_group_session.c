#include "olm/olm.h"
#include "ruby_olm.h"
#include "olm/inbound_group_session.h"

#include "olm/error.h"
#include "olm/olm_export.h"
#include "olm/outbound_group_session.h"
#include "olm/pk.h"
#include "olm/sas.h"

void eto_test(void){
    int a = 10;
    printf("A is: %d",a);
}

// https://www.rubyguides.com/2018/03/write-ruby-c-extension/
void eto_test2(VALUE self, VALUE encrypted_message){
    printf("ETO TEST 2 WORKING!");

    OlmInboundGroupSession *session;

    uint8_t session_key[] = "AQAAAADz8wPreSycltyuCrMhCSjstHB9X9i5HXoefY6dfHltzYX1FJJbvfy7KTN9E6RCHi2pKJ81JGWoqN3LqMa+xemDcakcTmPS4OS0PYwl2TcSf3qxZc2yeoqqJZ4IsyJ6hfd1GsuA12hr9gNrdkrlvDSPFioL8yk9sj07uRuD4ci2E397RTdVvcWAgjS11p/qTQ8uds3JNrq83Z7To0aHK/MX";
    size_t session_key_length = sizeof(session_key)/sizeof(uint8_t)-1;
    printf("SESSION KEY LENGTH: %d\n",session_key_length);
    //printf("SESSION ADDRESS: %p\n",&session);
    //printf("ADDRESS: %p\n",&session_key);

    int res = olm_init_inbound_group_session(&session, &session_key, session_key_length);
    if (res == -1) {
        printf("SOMETHING WENT WRONG... %d\n", res);
    }

    //obj = super().__new__(cls)
    //obj._buf = ffi.new("char[]", lib.olm_inbound_group_session_size())
    //obj._session = lib.olm_inbound_group_session(obj._buf)

    //printf(str);
    //OlmInboundGroupSession session;
    //byte_ciphertext = to_bytes(ciphertext)
    //ciphertext_buffer = ffi.new("char[]", byte_ciphertext)

    char * ciphertext_buffer = RSTRING_PTR(encrypted_message);
    int ciphertext_length = RSTRING_LEN(encrypted_message);
    printf("CIPHERTEXT LENGTH: %d\n",ciphertext_length);
    printf("\nCiphertext_buffer: ");
    for (int i = 0; i < ciphertext_length; ++i) {
        printf("%c", ciphertext_buffer[i]);
    }
    printf("\n");

    //int max_length = olm_group_decrypt_max_plaintext_length(session, ciphertext_buffer, ciphertext_length);
    //printf("Max length is: %d",max_length);

    //max_plaintext_length = lib.olm_group_decrypt_max_plaintext_length(
    //    self._session, ciphertext_buffer, len(byte_ciphertext)
    //)
}

// https://github.com/ruby/ruby/blob/master/doc/extension.rdoc
void inbound_group_session_init(void)
{
    VALUE cRubyOLM = rb_define_module("RubyOlm");    
    VALUE cInboundGroupSession = rb_define_class_under(cRubyOLM, "InboundGroupSession", rb_cObject);
    
    rb_define_method(cInboundGroupSession, "eto_test", eto_test, 0);
    rb_define_method(cInboundGroupSession, "eto_test2", eto_test2, 1);
}
