"use client"
import "./globals.css";

import BoardRoomWidget from "@/components/widgets/BoardRoomWidget";

export default function RootLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <html lang="en">
      <body>
        {children}
        <BoardRoomWidget />
      </body>
    </html>
  );
}