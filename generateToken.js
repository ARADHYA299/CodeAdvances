const jwt = require("jsonwebtoken");

module.exports = (userId, orgId, role) => {
  return jwt.sign(
    {
      userId,
      orgId,
      role,
    },
    process.env.JWT_SECRET,
    { expiresIn: "7d" },
  );
};
