enum GRANT_TYPE {
  AUTHORIZATION_CODE,
  IMPLICIT_GRANT,
  RESOURCE_OWNER_PASSWORD_CREDENTIAL,
  CLIENT_CREDENTIAL
};

class Client_Authorization {
public:
  GRANT_TYPE grant_type;
};