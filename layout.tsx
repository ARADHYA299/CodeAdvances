import React from 'react';
import { redirect } from 'next/navigation';
import { getSessionFromCookies } from '@/lib/auth';
import { Sidebar } from '@/components/Sidebar';

export default async function AdminLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  const user = await getSessionFromCookies();

  if (!user) {
    redirect('/login');
  }

  if (user.role !== 'ADMIN') {
    redirect('/resident');
  }

  return (
    <div className="flex-1 flex flex-col md:flex-row w-full max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-6 gap-6">
      <Sidebar role="ADMIN" />
      <div className="flex-1 min-w-0">{children}</div>
    </div>
  );
}
