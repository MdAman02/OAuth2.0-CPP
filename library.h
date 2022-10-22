#ifndef OAUTH2_0_CPP_LIBRARY_H
#define OAUTH2_0_CPP_LIBRARY_H

#include<map>

void hello();

namespace oAuth2 {
  enum CLIENT_TYPE {
    CONFIDENTIAL, PUBLIC
  };

  enum AUTH_GRANT_TYPE {
    AUTHORIZATION_CODE_GRANT,
    IMPLICIT_GRANT,
    RESOURCE_OWNER_PASSWORD_CREDENTIALS,
    CLIENT_CREDENTIALS
  };

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

  class AuthGrantRequest {
    public:
      AUTH_GRANT_TYPE type;
      std::string response_type; //depend on type
      std::string client_id;
      std::string redirect_url;
      std::map<std::string,std::string> scope;
  };

  class AuthGrantResponse {
  public:

  };

  class AuthGrantError : public std::exception {

  };

  class AuthGrant {
    public:
      virtual AuthGrantResponse getAuthorizationGrant (AuthGrantRequest req) = 0;
  };

  class Client {
  public:
    CLIENT_TYPE type;
    std::string client_id; // client identifier (code / token)
    std::string client_password; // For HTTP Basic Auth
    bool isRegistered;
    std::string redirection_url;
    std::map<std::string,std::string> state;
  };

  class accessToken {
  public:
    std::string token;
    std::map<std::string, std::string> scope;
  };

  class refreshToken {

  };
}

#endif //OAUTH2_0_CPP_LIBRARY_H
