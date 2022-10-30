#include<string>
#include<cmath>
#include<exception>
#include "models.hpp"
#include "repositories.hpp"

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

  // CLIENT_REPOSITORY //
  std::pair<std::string, std::string> ClientRepository::generateClientCredentials() {
    // use some uniqId
    return std::pair<std::string, std::string>();
  }

  const models::Client& ClientRepository::createClient (models::CLIENT_TYPE type, std::map<std::string, std::string> state, std::string redirUri) {
    std::pair<std::string, std::string> t = this->generateClientCredentials();
    const std::string clientId = t.first, clientSecret = t.second;
    const models::Client client(clientId, clientSecret, true, redirUri, state, models::CLIENT_TYPE::CONFIDENTIAL);
    return this->_provider[clientId] = client;
  }

  const models::Client* ClientRepository::getClient (std::string clientId) {
    try
    {
      models::Client &client = this->_provider.at(clientId);
      return &client;
    }
    catch(const std::exception& e)
    {
      return nullptr;
    }
  }

  const models::Client* ClientRepository::updateClient (std::string clientId, models::Client client) {
    if (client.client_id != clientId)
      throw "update object must have mathed clientId";
    this->_provider[clientId] = client;
    return &client;
  }
  
  bool ClientRepository::deleteClient (std::string clientId) {
    try {
      this->_provider.erase(clientId);
      return true;
    } catch(const std::exception& e) {
      return false;
    }
  }

  std::pair<bool, const models::Client*> ClientRepository::authenticateClient (std::string clientId, std::string clientSecret) {
    const models::Client* client = this->getClient(clientId);
    if (client == nullptr)
      return std::make_pair(false, nullptr);
    if (client->client_secret != clientSecret)
      return std::make_pair(false, client);
    return std::make_pair(true, client);
  }
}
