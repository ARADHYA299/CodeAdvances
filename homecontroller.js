const path = require('path');

exports.get_add_home = (req, res,next) => {
  res.sendFile(path.join(__dirname, "../Views", "Add.html"));
};