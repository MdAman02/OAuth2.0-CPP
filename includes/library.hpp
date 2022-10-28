#ifndef OAUTH2_0_CPP_LIBRARY_H
#define OAUTH2_0_CPP_LIBRARY_H

#include<map>

void hello();

namespace oAuth2 {
  enum AUTH_GRANT_ERROR_CODE {
    INVALID_REQUEST,
    UNAUTHORIZED_CLIENT,
    ACCESS_DENIED,
    UNSUPPORTED_RESPONSE_TYPE,
    INVALID_SCOPE,
    SERVER_ERROR,
    TEMPORARY_UNAVAILABLE,
  };

  // Resource Owner Authorization

  class tokenIssuer {

  };

  class OAuth {
  protected:
    virtual void postGrantCallback () = 0;
  public:
    virtual void generateAuthGrant() = 0;
    virtual void issueAccessToken() = 0;
    virtual void validateAccessToken() = 0;
    virtual void refreshAccessToken() = 0;
  };

}

#endif //OAUTH2_0_CPP_LIBRARY_H
