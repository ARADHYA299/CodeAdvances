const express = require("express");
const router = express.Router();
const authMiddleware = require("../middleware/auth.middleware");
const upload = require("../middleware/uploadMiddleware");
const requirerole = require("../middleware/roleMiddleware");

const {
  uploadDocument,
  getDocuments,
  deleteDocuments,
} = require("../controllers/documentController");

router.post("/upload", authMiddleware, upload.single("file"), uploadDocument);
router.get("/", authMiddleware, getDocuments);

router.delete("/:id", authMiddleware, requirerole("admin"), deleteDocuments);

module.exports = router;
