const pool = require("../config/db");
const fs = require("fs");
const path = require("path");
const { getEmbedding } = require("./embedding");
const { chunkText } = require("./chunkService");
const chunkModel = require("../models/chunkModel");

exports.processDocument = async (document) => {
  try {
    console.log("Processing document:", document);
    await pool.query(
      `UPDATE documents SET processing_status = 'processing' WHERE id = $1`,
      [document.id],
    );
    // The Text Pipeline
    /*1--> Reading the document */

    const filePath = path.resolve("uploads", document.file_url);

    // Extracted text from the doc

    const extractedText = fs.readFileSync(filePath, "utf-8");

    // chunking the extracted text into smaller pieces of 500 characters each and storing them in the database

    const chunks = chunkText(extractedText, 500);

    for (let i = 0; i < chunks.length; i++) {
      await chunkModel.createChunk(document.id, document.org_id, i, chunks[i]);
    }

    // generating embedding for the extracted text and storing it in the database

    const embedding = await getEmbedding(extractedText);

    //storage query to update the document with the extracted text and embedding

    await pool.query(
      `UPDATE documents SET extracted_text = $1 , embedding = $2, processing_status = 'completed' WHERE id = $3`,
      [extractedText, embedding, document.id],
    );
  } catch (error) {
    console.error("Error processing document:", error);
    await pool.query(
      `UPDATE documents SET processing_status = 'failed' WHERE id = $1`,
      [document.id],
    );
  }
};
