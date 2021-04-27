const fs = require('fs')
const express = require("express");
const router = express.Router();

router.get("/", (req, res) => {
var blockId = req.query.blockId;
  console.log(req.query.blockId);

//  res.send({ response: "I am alive" }).status(200);

  fs.readFile('data/'+blockId+'.json', 'utf8' , (err, data) => {
    if (err) {
      console.error(err)
      return
    }
    console.log(data)
    res.send(JSON.parse(data)).status(200);
  })

});


module.exports = router;