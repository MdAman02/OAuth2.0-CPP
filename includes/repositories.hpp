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

    class ClientRepository {
    private:
      std::map<std::string, models::Client> _provider; // clientId to Client object
      std::pair<std::string, std::string> generateClientCredentials();
    public:
      const models::Client& createClient (models::CLIENT_TYPE type, std::map<std::string, std::string> state, std::string redirection_uri);
      const models::Client* getClient (std::string clientId);
      const models::Client* updateClient (std::string clientId, models::Client client);
      bool deleteClient (std::string clientId);
    };
}
