const pool = require("../config/db");

exports.createDocument = async (orgId, userId, originalname, filename) => {
  const result = await pool.query(
    `INSERT INTO documents (org_id, uploaded_by, title, file_url, processing_status)
VALUES ($1, $2, $3, $4, 'pending') RETURNING *;`,
    [orgId, userId, originalname, filename],
  );
  return result.rows[0];
};

exports.getDocumentsByOrg = async (orgId, limit, offset) => {
  const dataQuery = await pool.query(
    `SELECT id, title, file_url, processing_status, created_at
     FROM documents
     WHERE org_id = $1
     ORDER BY created_at DESC
     LIMIT $2 OFFSET $3`,
    [orgId, limit, offset],
  );
  const countQuery = await pool.query(
    `SELECT COUNT(*) FROM documents WHERE org_id = $1`,
    [orgId],
  );

  return {
    documents: dataQuery.rows,
    total: parseInt(countQuery.rows[0].count, 10),
  };
};

exports.deletedocument = async (docId, orgId) => {
  const result = await pool.query(
    `DELETE FROM documents
     WHERE id = $1 AND org_id = $2
     RETURNING *`,
    [docId, orgId],
  );

  return result.rows[0];
};
