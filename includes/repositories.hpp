#include<map>
#include "models.hpp"

namespace repository {
  class userRepository {
  private:
    std::map<std::string, models::User> provider; // userId to User model association
  public:
    userRepository();
    models::User getUser (std::string userId);
  };

  class accessTokenRepository {
  private:
    std::map<std::string, models::AccessToken> provider; // token to accessToken model map
  public:
    accessTokenRepository();
    models::AccessToken* getToken (std::string token);
    models::AccessToken createToken(std::string clientId, std::string userId, std::vector<std::string> claims);
    models::AccessToken createToken(std::string userId);
    bool revokeAccessToken(std::string token);
  };

  class authGrantRepository {
  private:
    std::map<std::string, models::AuthGrant> provider;
  public:
    authGrantRepository();
    models::AuthGrant* getGrant (std::string authenticationCode);
    models::AuthGrant createGrant(std::string clientId, std::string userId, std::vector<std::string> permissions);
    bool revokeGrant(std::string authenticationCode);
  };
}
