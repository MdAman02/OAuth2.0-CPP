#include "library.h"

namespace oAuth2 {
  enum GRANT_TYPE {
    AUTHORIZATION_CODE,
    IMPLICIT_GRANT,
    RESOURCE_OWNER_PASSWORD_CREDENTIAL,
    CLIENT_CREDENTIAL
  };

  class Client_Authorization: public oAuth2::AuthGrant {
  public:
    oAuth2::AuthGrantResponse getAuthorizationGrant(oAuth2::AuthGrantRequest req) {
        
    }
  };
}
