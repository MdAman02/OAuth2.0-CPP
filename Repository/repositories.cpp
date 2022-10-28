#include<string>
#include<cmath>
#include<exception>
#include "models.hpp"
#include "repositories.h"

// demo user data
std::string userId1 = "dasd-dsa54-gfd87-fghg3";
std::string userName1 = "userAman";
std::string email1 = "test@test.com";
std::string passWordHash1 = "dsadsagfdsgfd";

// demo client
std::string clientId = "gfd-nvb-ter-bfg76";
std::string clientSecret = "fds6gdsf-gdsfg-67-vsefs";
models::AUTH_GRANT_TYPE type;
std::string url = "refdirect.to";
std::map<std::string, std::string> state;

const std::time_t DEFAULT_ACCESS_TOKEN_EXPIRATION;
const std::time_t DEFAULT_CLIENT_AUTH_CODE_EXPIRATION;

std::string generateUuid () {
  return "fadsf-garsgf-gdfgf" + rand();
}

namespace repository {
  // User Repository
  userRepository::userRepository() {
    models::User user1(userId1, userName1, email1, passWordHash1);
    this->provider[userId1] = user1;
  };

  models::User userRepository::getUser (std::string userId) {
    return this->provider[userId];
  }

  // Access token Repository
  accessTokenRepository::accessTokenRepository() {}
  models::AccessToken accessTokenRepository::createToken (std::string clientId, std::string userId, std::vector<std::string> claims) {
    std::string uuid = generateUuid();
    const models::AccessToken accessToken(uuid, userId, clientId, claims, DEFAULT_ACCESS_TOKEN_EXPIRATION);
    this->provider[uuid] = accessToken;
    return accessToken;
  }

  models::AccessToken accessTokenRepository::createToken (std::string userId) {
    std::string uuid = generateUuid();
    const models::AccessToken accessToken(uuid, userId, DEFAULT_ACCESS_TOKEN_EXPIRATION);
    this->provider[uuid] = accessToken;
    return accessToken;
  }

  models::AccessToken* accessTokenRepository::getToken (std::string token) {
    try
    {
      models::AccessToken &accessToken = this->provider.at(token);
      return &accessToken;
    }
    catch(const std::exception& e)
    {
      return nullptr;
    }
  }

  bool accessTokenRepository::revokeAccessToken (std::string token) {
    models::AccessToken* accessToken = this->getToken(token);
    if (accessToken == nullptr) {
      throw "No existing Access Token found";
    }
    return accessToken->isExpired = true;
  }

  models::AuthGrant* authGrantRepository::getGrant (std::string code) {
    try
    {
      models::AuthGrant &authGrant = this->provider.at(code);
      return &authGrant;
    }
    catch(const std::exception& e)
    {
      return nullptr;
    }
  }

  models::AuthGrant authGrantRepository::createGrant (std::string clientId, std::string userId, std::vector<std::string> permissions) {
    models::AUTH_GRANT_TYPE grantType = models::AUTH_GRANT_TYPE::AUTHORIZATION_CODE_GRANT;
    std::string authCode = generateUuid();
    const models::AuthGrant authGrant(grantType, authCode, clientId, userId, permissions, DEFAULT_CLIENT_AUTH_CODE_EXPIRATION);
    return authGrant;
  }

  bool authGrantRepository::revokeGrant (std::string code) {
    models::AuthGrant* authGrant = this->getGrant(code);
    if (authGrant == nullptr) {
      throw "Client Authorization Code doesnt exist";
    }
    return authGrant->isExpired = true;
  }
}
