const pool = require("../config/db");

exports.getOrgAnalytics = async (orgId) => {
  const result = await pool.query(
    `SELECT COUNT(*) FROM documents WHERE org_id = $1`,
    [orgId],
  );

  const weeklyDocs = await pool.query(
    `SELECT COUNT(*) FROM documents WHERE org_id = $1 AND created_at >= NOW() - INTERVAL '7 days'`,
    [orgId],
  );

  const totalUsers = await pool.query(
    `SELECT COUNT(*) FROM users WHERE org_id = $1`,
    [orgId],
  );

  const roleBreakdown = await pool.query(
    `SELECT role, COUNT(*) FROM users WHERE org_id = $1 GROUP BY role`,
    [orgId],
  );

  return {
    totalDocuments: parseInt(result.rows[0].count),
    weeklyDocuments: parseInt(weeklyDocs.rows[0].count),
    totalUsers: parseInt(totalUsers.rows[0].count),
    roleBreakdown: roleBreakdown.rows,
  };
};
