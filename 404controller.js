const path = require('path');

exports.error_c = (req, res, next) => {
  res.status(404).sendFile(path.join(__dirname, "../Views", "error.html"));
};