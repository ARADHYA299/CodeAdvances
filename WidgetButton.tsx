"use client"

import {motion} from "framer-motion"

interface props{
  onClick: () => void
}

export default function WidgetButton({onClick} : props){
  return (
    <motion.button
      onClick={() => {
        console.log("Button clicked");
        onClick();
      }}
      initial={{ scale: 1 }}
      animate={{ scale: 1 }}
      whileHover={{ scale: 1.1 }}
      className="fixed bottom-6 right-6 z-50
flex items-center justify-center
w-12 h-12
rounded-full
bg-gradient-to-br from-purple-600 to-violet-500
text-white font-semibold
shadow-lg shadow-purple-500/20
hover:scale-110 active:scale-95
transition-all duration-200"
    >
      AI
    </motion.button>
  )
}