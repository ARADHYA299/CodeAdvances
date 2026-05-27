const home = require("../models/home");

exports.usercontrol = () => {
  return (res) => {
    home.fetch((homes) => {
      res.render("Home", { registeredHomes: homes });
    });
  };
};
