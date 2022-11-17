#include "repositories.hpp"
#include "library.hpp"

#include "iostream"
#include "cmath"

namespace oAuth2 {
  // MISC
  // ToDo: Use some UUid library
  const std::string generateAuthCode() {
    return std::string("auth grant code") + (char)rand();
  }

  std::time_t DEFAULT_AUTH_GRANT_EXP;

  // clientAuthentication
  std::pair<bool, const models::Client*> clientAuthentication::authenticateClient(std::string client_id, std::string client_secret) {
    const models::Client* client = this->_clientRepository.getClient(client_id);
    if (client == nullptr)
      return std::make_pair(false, nullptr);
    if (client->client_secret != client_secret)
      return std::make_pair(false, client);
    return std::make_pair(true, client);
  }

  // req grant -> validate req -> authenticate from user -> generate code grant -> redirect with code grant

  // clientAuthorization
  models::AuthGrant clientAuthorization::getAuthGrant(requestResponseModels::authGrantRequest authGrantReq) {
    if (authGrantReq.response_type != "code")
      throw new requestResponseModels::authGrantError(
        requestResponseModels::authGrantErrorCodes::unsupportedResp,
        "Invalid response type provided"
      );

    const models::Client* client = this->_clientRepository.getClient(authGrantReq.client_id);
    if (client == nullptr)
      throw new requestResponseModels::authGrantError(
        requestResponseModels::authGrantErrorCodes::accessDenied,
        "Unrecognized Client"
      );

    const std::string authCode = generateAuthCode();
    const models::AuthGrant authGrant(
      models::AUTH_GRANT_TYPE::AUTHORIZATION_CODE_GRANT,
      authCode,
      authGrantReq.client_id,
      "mockUserID", // should be coming from user redirection, ToDo: may be split it up into two separate func?
      authGrantReq.scope,
      DEFAULT_AUTH_GRANT_EXP
    );

    return authGrant;
  }
}
