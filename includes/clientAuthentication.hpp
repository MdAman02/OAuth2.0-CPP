#include "models.hpp"

namespace oAuth2 {
  enum class GRANT_TYPE {
    AUTHORIZATION_CODE,
    IMPLICIT_GRANT,
    RESOURCE_OWNER_PASSWORD_CREDENTIAL,
    CLIENT_CREDENTIAL
  };
}
