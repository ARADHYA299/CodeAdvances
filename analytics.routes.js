const express = require("express");
const router = express.Router();
const authMiddleware = require("../middleware/auth.middleware");
const { getOverview } = require("../controllers/analyticscontroller");

router.get("/overview", authMiddleware, getOverview);

module.exports = router;
