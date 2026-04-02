


class Response
   {
   public:
       int statusCode;
       std::string body;
       std::map<std::string, std::string> headers;
   
       std::string toString() const;
   };