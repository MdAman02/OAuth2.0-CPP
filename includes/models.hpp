#include<string>
#include<ctime>
#include<vector>
#include<map>

// POCOs //
namespace models {
  enum class CLIENT_TYPE {
    CONFIDENTIAL, PUBLIC
  };

  enum class AUTH_GRANT_TYPE {
    AUTHORIZATION_CODE_GRANT,
    IMPLICIT_GRANT,
    RESOURCE_OWNER_PASSWORD_CREDENTIALS,
    CLIENT_CREDENTIALS
  };

  class User {
  public:
    User(std::string id, std::string name, std::string email, std::string hash): 
      userId(id), userName(name), email(email), passWordHash(hash) {}

    std::string userId;
    std::string userName;
    std::string email;
    std::string passWordHash;
  };

  class Client {
  public:
    Client (
      std::string id,
      std::string secret,
      bool isReg,
      std::string url,
      std::map<std::string,std::string> state,
      CLIENT_TYPE type
    ) : client_id(id), client_secret(secret), isRegistered(isReg), redirection_url(url), state(state), type(type) {}

    CLIENT_TYPE type;
    std::string client_id; // client identifier (code / token)
    std::string client_secret;
    std::string password_hash; // For HTTP Basic Auth
    bool isRegistered;
    std::string redirection_url;
    std::map<std::string,std::string> state;
  };

  class AccessToken {
  public:
    AccessToken() {}
    // issue for self
    AccessToken(
      std::string token,
      std::string userId,
      std::time_t exp
    ) : token(token), userId(userId), expiration(exp), isResourceOwner(true) {}

    // issue for client
    AccessToken(
      std::string token,
      std::string userId,
      std::string clientId,
      std::vector<std::string> claims,
      std::time_t exp
    ) : token(token), userId(userId), clientId(clientId), claims(claims), expiration(exp), isResourceOwner(false) {}

    std::string token;
    std::string userId; // Reference
    std::string clientId;
    bool isResourceOwner;
    bool isExpired;
    std::vector<std::string> claims;
    std::time_t expiration;
  };

  class AuthGrant {
  public:
    AuthGrant() {}
    AuthGrant(
      AUTH_GRANT_TYPE type,
      std::string code,
      std::string clientId,
      std::string userId,
      std::vector<std::string> permissions,
      std::time_t exp
    ) : type(type), code(code), clientId(clientId), permissions(permissions), expiration(exp) {}

    AUTH_GRANT_TYPE type;
    const std::string code;
    const std::string clientId;
    const std::string userId;
    std::vector<std::string> permissions;
    std::time_t expiration;
    bool isExpired;
  };
}
