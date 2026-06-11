const processor = require("../services/documentProcessor");

const documentModel = require("../models/documentModel");
exports.uploadDocument = async (req, res) => {
  try {
    const orgId = req.user.orgId;
    const userId = req.user.userId;

    const { originalname, filename } = req.file;

    const document = await documentModel.createDocument(
      orgId,
      userId,
      originalname,
      filename,
    );

    processor.processDocument(document).catch(console.error);

    res.status(201).json(document);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
};

exports.getDocuments = async (req, res) => {
  try {
    const orgId = req.user.orgId;
    console.log("Fetching documents for org:", req.user.orgId);
    const page = parseInt(req.query.page, 10) || 1;
    const limit = parseInt(req.query.limit, 10) || 5;
    const offset = (page - 1) * limit;
    const result = await documentModel.getDocumentsByOrg(orgId, limit, offset);

    res.json({
      page,
      limit,
      total: result.total,
      totalPages: Math.ceil(result.total / limit),
      data: result.documents,
    });
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
};

exports.deleteDocuments = async (req, res) => {
  try {
    const docId = req.params.id;
    const orgId = req.user.orgId;

    const deleted = await documentModel.deletedocument(docId, orgId);

    if (!deleted) {
      return res.status(404).json({ message: "Document not found" });
    }

    res.json({ message: "Document Deleted Successfully" });
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
};
