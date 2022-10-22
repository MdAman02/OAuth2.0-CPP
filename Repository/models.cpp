#include<string>

namespace models {
  class User {
  public:
    std::string userId;
    std::string name;
    std::string email;
  };

  class accessToken {
  public:
    std::string token;
    std::string userId; // Reference
    std::string permissions;
  };
}