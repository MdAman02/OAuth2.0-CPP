#include "models.hpp"

namespace oAuth2 {
  enum class GRANT_TYPE {
    AUTHORIZATION_CODE,
    IMPLICIT_GRANT,
    RESOURCE_OWNER_PASSWORD_CREDENTIAL,
    CLIENT_CREDENTIAL
  };

  class clientAuthentication {
    public:
      static models::Client authenticateClient (std::string client_id, std::string client_secret);
  };

  class authGrantRequest {
    public:
      std::string response_type;
      std::string client_id;
      std::string redirect_uri;
      std::vector<std::string> scope;
      std::vector<std::string> state;
  };

  class clientAuthorization {
    public:
      static models::AuthGrant getAuthGrant (authGrantRequest authGrantReq);
  };

  class requestAccessToken {
    public:
      static models::AccessToken issueToken (models::AuthGrant grant);
  };
}
