'use client';

import React, { useState, useEffect } from 'react';
import Link from 'next/link';
import {
  ClipboardList,
  Clock,
  Loader2,
  CheckCircle2,
  AlertTriangle,
  ArrowRight,
  TrendingUp,
  Settings,
  ShieldAlert,
} from 'lucide-react';
import { DashboardStats } from '@/lib/types';
import { DashboardCharts } from '@/components/DashboardCharts';
import { StatusBadge } from '@/components/StatusBadge';

export default function AdminDashboardPage() {
  const [stats, setStats] = useState<DashboardStats | null>(null);
  const [loading, setLoading] = useState(true);

  const fetchStats = async () => {
    setLoading(true);
    try {
      const res = await fetch('/api/dashboard');
      if (res.ok) {
        const data = await res.json();
        setStats(data.stats);
      }
    } catch (err) {
      console.error('Failed to fetch dashboard stats:', err);
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchStats();
  }, []);

  if (loading) {
    return (
      <div className="p-12 text-center bg-white dark:bg-dark-card rounded-3xl border border-slate-200/80 dark:border-dark-border">
        <Loader2 className="w-8 h-8 text-sky-600 dark:text-sky-400 animate-spin mx-auto mb-2" />
        <p className="text-xs text-slate-500 dark:text-slate-400 font-medium">Loading society dashboard telemetry...</p>
      </div>
    );
  }

  if (!stats) {
    return (
      <div className="p-8 text-center bg-white dark:bg-dark-card rounded-3xl border border-slate-200/80 dark:border-dark-border">
        <p className="text-xs text-slate-500 dark:text-slate-400">Failed to load statistics.</p>
      </div>
    );
  }

  const statusPieData = [
    { status: 'Open', count: stats.openComplaints, color: '#f59e0b' },
    { status: 'In Progress', count: stats.inProgressComplaints, color: '#0ea5e9' },
    { status: 'Resolved', count: stats.resolvedComplaints, color: '#10b981' },
  ];

  return (
    <div className="space-y-6">
      {/* Top Banner */}
      <div className="flex flex-col sm:flex-row sm:items-center justify-between gap-4">
        <div>
          <span className="text-[10px] font-extrabold text-indigo-600 dark:text-indigo-400 uppercase tracking-widest">
            Management & Telemetry
          </span>
          <h1 className="text-2xl sm:text-3xl font-black text-slate-900 dark:text-white tracking-tight">
            Society Maintenance Dashboard
          </h1>
          <p className="text-xs text-slate-500 dark:text-slate-400 mt-1 font-medium">
            Real-time complaint telemetry, facility distribution, and overdue alert tracking
          </p>
        </div>

        <div className="flex items-center gap-2">
          <Link
            href="/admin/settings"
            className="inline-flex items-center gap-1.5 px-4 py-2 rounded-2xl text-xs font-bold bg-white dark:bg-dark-card text-slate-700 dark:text-slate-200 border border-slate-200/80 dark:border-dark-border hover:bg-slate-50 dark:hover:bg-slate-800 shadow-card-light dark:shadow-card-dark transition-colors"
          >
            <Settings className="w-4 h-4 text-slate-400" />
            <span>Threshold: {stats.overdueThresholdDays} Days</span>
          </Link>

          <Link
            href="/admin/complaints"
            className="inline-flex items-center gap-1.5 px-4 py-2 rounded-2xl text-xs font-bold bg-gradient-to-r from-sky-600 to-indigo-600 hover:from-sky-700 hover:to-indigo-700 text-white shadow-md shadow-sky-500/20 transition-all hover:scale-105"
          >
            <span>Manage All</span>
            <ArrowRight className="w-4 h-4" />
          </Link>
        </div>
      </div>

      {/* Overdue Urgent Alert Banner if count > 0 */}
      {stats.overdueComplaints > 0 && (
        <div className="p-5 rounded-3xl bg-gradient-to-r from-rose-600 via-red-600 to-rose-700 text-white shadow-glow-rose flex flex-col sm:flex-row items-start sm:items-center justify-between gap-4">
          <div className="flex items-center gap-3.5">
            <div className="p-3 rounded-2xl bg-white/20 backdrop-blur-md shrink-0">
              <ShieldAlert className="w-6 h-6 text-white" />
            </div>
            <div>
              <h4 className="font-extrabold text-sm sm:text-base">
                Critical SLA Notice: {stats.overdueComplaints} Overdue Complaint{stats.overdueComplaints > 1 ? 's' : ''} Require Attention
              </h4>
              <p className="text-xs text-rose-100 opacity-90 mt-0.5">
                These requests have exceeded the {stats.overdueThresholdDays}-day resolution threshold and are surfaced at the top of the queue.
              </p>
            </div>
          </div>

          <Link
            href="/admin/complaints?overdueOnly=true"
            className="inline-flex items-center gap-1.5 px-4 py-2 rounded-2xl text-xs font-black bg-white text-rose-700 hover:bg-rose-50 transition-colors shrink-0 shadow-sm hover:scale-105"
          >
            <span>Review Overdue Queue</span>
            <ArrowRight className="w-3.5 h-3.5" />
          </Link>
        </div>
      )}

      {/* Summary KPI Cards */}
      <div className="grid grid-cols-2 sm:grid-cols-3 lg:grid-cols-5 gap-3.5">
        <div className="bg-white dark:bg-dark-card p-4 sm:p-5 rounded-3xl border border-slate-200/80 dark:border-dark-border shadow-card-light dark:shadow-card-dark transition-all hover:-translate-y-0.5 duration-200">
          <span className="text-[10px] font-extrabold text-slate-400 dark:text-slate-400 uppercase tracking-widest block mb-1">
            Total Complaints
          </span>
          <div className="text-2xl sm:text-3xl font-black text-slate-900 dark:text-white">{stats.totalComplaints}</div>
          <div className="mt-2 text-[11px] text-slate-500 dark:text-slate-400 flex items-center gap-1 font-semibold">
            <TrendingUp className="w-3.5 h-3.5 text-sky-500" />
            <span>Lifetime volume</span>
          </div>
        </div>

        <div className="bg-white dark:bg-dark-card p-4 sm:p-5 rounded-3xl border border-slate-200/80 dark:border-dark-border shadow-card-light dark:shadow-card-dark transition-all hover:-translate-y-0.5 duration-200">
          <span className="text-[10px] font-extrabold text-amber-600 dark:text-amber-400 uppercase tracking-widest block mb-1">
            Pending / Open
          </span>
          <div className="text-2xl sm:text-3xl font-black text-amber-600 dark:text-amber-400">{stats.openComplaints}</div>
          <div className="mt-2 text-[11px] text-slate-500 dark:text-slate-400 flex items-center gap-1 font-semibold">
            <Clock className="w-3.5 h-3.5 text-amber-500" />
            <span>Awaiting triage</span>
          </div>
        </div>

        <div className="bg-white dark:bg-dark-card p-4 sm:p-5 rounded-3xl border border-slate-200/80 dark:border-dark-border shadow-card-light dark:shadow-card-dark transition-all hover:-translate-y-0.5 duration-200">
          <span className="text-[10px] font-extrabold text-sky-600 dark:text-sky-400 uppercase tracking-widest block mb-1">
            In Progress
          </span>
          <div className="text-2xl sm:text-3xl font-black text-sky-600 dark:text-sky-400">{stats.inProgressComplaints}</div>
          <div className="mt-2 text-[11px] text-slate-500 dark:text-slate-400 flex items-center gap-1 font-semibold">
            <Loader2 className="w-3.5 h-3.5 text-sky-500" />
            <span>Staff dispatched</span>
          </div>
        </div>

        <div className="bg-white dark:bg-dark-card p-4 sm:p-5 rounded-3xl border border-slate-200/80 dark:border-dark-border shadow-card-light dark:shadow-card-dark transition-all hover:-translate-y-0.5 duration-200">
          <span className="text-[10px] font-extrabold text-emerald-600 dark:text-emerald-400 uppercase tracking-widest block mb-1">
            Resolved
          </span>
          <div className="text-2xl sm:text-3xl font-black text-emerald-600 dark:text-emerald-400">{stats.resolvedComplaints}</div>
          <div className="mt-2 text-[11px] text-slate-500 dark:text-slate-400 flex items-center gap-1 font-semibold">
            <CheckCircle2 className="w-3.5 h-3.5 text-emerald-500" />
            <span>Closed tickets</span>
          </div>
        </div>

        <div className="bg-rose-500/10 dark:bg-rose-950/30 p-4 sm:p-5 rounded-3xl border border-rose-300 dark:border-rose-800 shadow-glow-rose col-span-2 sm:col-span-1 transition-all hover:-translate-y-0.5 duration-200">
          <span className="text-[10px] font-extrabold text-rose-600 dark:text-rose-400 uppercase tracking-widest block mb-1">
            Overdue (&gt;{stats.overdueThresholdDays}d)
          </span>
          <div className="text-2xl sm:text-3xl font-black text-rose-600 dark:text-rose-400">{stats.overdueComplaints}</div>
          <div className="mt-2 text-[11px] text-rose-600 dark:text-rose-400 font-bold flex items-center gap-1">
            <AlertTriangle className="w-3.5 h-3.5" />
            <span>Priority action</span>
          </div>
        </div>
      </div>

      {/* Visual Analytics Charts */}
      <DashboardCharts
        categoryData={stats.categoryBreakdown}
        statusData={statusPieData}
      />

      {/* Recent Lifecycle Activity Feed */}
      <div className="bg-white dark:bg-dark-card p-6 sm:p-7 rounded-3xl border border-slate-200/80 dark:border-dark-border shadow-card-light dark:shadow-card-dark transition-colors duration-200">
        <div className="flex items-center justify-between mb-4">
          <div>
            <h3 className="text-xs font-extrabold text-slate-900 dark:text-white uppercase tracking-widest">
              Recent Lifecycle Events
            </h3>
            <p className="text-xs text-slate-500 dark:text-slate-400 mt-0.5">
              Live audit trail of complaint status transitions and manager notes
            </p>
          </div>
          <Link
            href="/admin/complaints"
            className="text-xs font-extrabold text-sky-600 dark:text-sky-400 hover:underline"
          >
            View all queue
          </Link>
        </div>

        <div className="divide-y divide-slate-100 dark:divide-slate-800">
          {stats.recentActivity.map((act) => (
            <div key={act.id} className="py-3.5 flex flex-col sm:flex-row sm:items-center justify-between gap-2">
              <div className="flex items-center gap-3">
                <StatusBadge status={act.toStatus} size="sm" />
                <div>
                  <div className="text-xs font-bold text-slate-800 dark:text-slate-200 flex items-center gap-1.5">
                    <span className="font-mono text-slate-500 dark:text-slate-400">{(act as any).complaint?.ticketNumber || 'Ticket'}:</span>
                    <span>{(act as any).complaint?.title || ''}</span>
                  </div>
                  {act.note && (
                    <p className="text-[11px] text-slate-500 dark:text-slate-400 italic mt-0.5">
                      "{act.note}" &bull; by {act.actorName} ({act.actorRole})
                    </p>
                  )}
                </div>
              </div>

              <time className="text-[11px] text-slate-400 dark:text-slate-400 font-mono shrink-0">
                {new Date(act.createdAt).toLocaleString()}
              </time>
            </div>
          ))}
        </div>
      </div>
    </div>
  );
}
