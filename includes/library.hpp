#ifndef OAUTH2_0_CPP_LIBRARY_H
#define OAUTH2_0_CPP_LIBRARY_H

#include "exception"
#include "repositories.hpp"

namespace requestResponseModels {
  // standard auth grant error codes
  struct authGrantErrorCodes {
    static const std::string invalidReq;
    static const std::string unAuthorizedClient;
    static const std::string accessDenied;
    static const std::string unsupportedResp;
    static const std::string invalidScope;
    static const std::string serverError;
    static const std::string tempUnavailable;
  };

  const std::string authGrantErrorCodes::invalidReq = "invalid_request";
  const std::string authGrantErrorCodes::unAuthorizedClient = "unauthorized_client";
  const std::string authGrantErrorCodes::accessDenied = "access_denied";
  const std::string authGrantErrorCodes::unsupportedResp = "unsupported_response_type";
  const std::string authGrantErrorCodes::invalidScope = "invalid_scope";
  const std::string authGrantErrorCodes::serverError = "server_error";
  const std::string authGrantErrorCodes::tempUnavailable = "temporarily_unavailable";

  class authGrantRequest {
    public:
      std::string response_type;
      std::string client_id;
      std::string redirect_uri;
      std::vector<std::string> scope;
      std::vector<std::string> state;
  };

class authGrantResponse {
  public:
    std::string code;
    std::vector<std::string> state;
  };

  class authGrantError : public std::exception {
  public:
    authGrantError(std::string error, std::string errorDesc) {
      this->error = error;
      this->error_description = errorDesc;
    }

    std::string what() {
      return this->error_description;
    }
    std::string error;
    std::string error_description;
    std::string error_uri;
    std::vector<std::string> state;
  };
};

namespace oAuth2 {
  enum class GRANT_TYPE {
    AUTHORIZATION_CODE,
    IMPLICIT_GRANT,
    RESOURCE_OWNER_PASSWORD_CREDENTIAL,
    CLIENT_CREDENTIAL
  };

  class clientAuthentication {
  private:
    repository::ClientRepository _clientRepository;
  public:
    clientAuthentication(repository::ClientRepository clientRepository) {
      this->_clientRepository = clientRepository;
    }
    std::pair<bool, const models::Client*> authenticateClient (std::string client_id, std::string client_secret);
  };

  class clientAuthorization {
  private:
    repository::ClientRepository _clientRepository;
    void authenticateResourceOwner (models::AuthGrant authGrant)
  public:
    clientAuthorization(repository::ClientRepository clientRepository) {
      this->_clientRepository = clientRepository;
    };
    models::AuthGrant getAuthGrant (requestResponseModels::authGrantRequest authGrantReq);
  };

  class requestAccessToken {
  public:
    static models::AccessToken issueToken (models::AuthGrant grant);
  };
}

#endif //OAUTH2_0_CPP_LIBRARY_H
