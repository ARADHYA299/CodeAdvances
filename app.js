const express = require('express');

const app = express();
const challenges = [
  {id : 1 , title : 'Binary search Tree' , description : 'Determine whether the given tree is a bst '},
  {id : 2 , title : 'Height of binary tree' , description : 'Determine the height of the binary tree'}
]

app.get('/challenge/:id' , (req,res) =>{
  const challenge = challenges.find(c => c.id === req.params.id);
  if(challenges) res.json(challenges);
  else res.status(404).send('Challenge not found');
})

app.listen(3003 , () => console.log('Sever running on http://localhost:3003'));