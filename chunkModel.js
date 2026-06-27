const pool = require("../config/db");

exports.createChunk = async (document_id, org_id, chunk_index, chunk_text) => {
  await pool.query(
    `INSERT INTO document_chunks (document_id, org_id, chunk_index, chunk_text) VALUES ($1, $2, $3, $4)`,
    [document_id, org_id, chunk_index, chunk_text],
  );
};

exports.getChunksByDocumentId = async (document_id) => {
  const result = await pool.query(
    `SELECT *
    FROM document_chunks
    WHERE document_id = $1
    ORDER BY chunk_index `,
    [document_id],
  );
  return result.rows;
};
