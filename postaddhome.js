const path = require("path");
const Home_m = require("../models/home");
const home = require("../models/home");

exports.post_add_home = () => {
  return (req, res) => {
    const home = new Home_m(
      req.body.Housename || "Untitled House",
      req.body.HomeType,
      req.body.Location,
      req.body.Guests,
      req.body.Bedrooms,
      req.body.Beds,
      Array.isArray(req.body.Amenities)
        ? req.body.Amenities
        : [req.body.Amenities],
      req.body.Description,
      req.body.Price
    );
    home.save();
    res.sendFile(path.join(__dirname, "../Views", "Reg.html"));
  };
};
