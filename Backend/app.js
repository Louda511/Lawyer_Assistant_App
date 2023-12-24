import { config } from "dotenv";
config();
let { PGHOST, PGDATABASE, PGUSER, PGPASSWORD, ENDPOINT_ID } = process.env;

import fs from "fs";
import express from 'express';
import postgres from "postgres";
import cors from "cors";
import OpenAI from "openai";

const sql = postgres({
  host: PGHOST,
  database: PGDATABASE,
  username: PGUSER,
  password: PGPASSWORD,
  port: 5432,
  ssl: 'require',
  connection: {
    options: `project=${ENDPOINT_ID}`,
  },
});


// DATABASE FUNCTIONS
// Get database version
async function getPgVersion() {
  const result = await sql`select version()`;
  console.log("Database Connected\n" , result[0].version);
}

// createAccount(name, password, jobtitle, type, email, sup_id)
async function createAccount(name, password, job_title, type, email, sup_id) {
  const result = await sql`INSERT INTO lawyer (name, password, job_title, type, email, sup_id)
  VALUES
     (${name}, ${password}, ${job_title}, ${type}, ${email}, ${sup_id});`;
  console.log(result);
  return result;
}

// check if account exists with email and password
async function login(email, password) {
  const result = await sql`
    SELECT *
    FROM lawyer
    WHERE email = ${email} AND password = ${password}
  `;
  console.log(result);

  // Check if a lawyer exists based on the query result
  if (result.length > 0) {
    console.log('Lawyer exists!');
  } else {
    console.log('Lawyer does not exist.');
  }
  return result;
}

// check if account exists with email
async function checkEmail(email) {
  const result = await sql`
    SELECT *
    FROM lawyer
    WHERE email = ${email}
  `;
  console.log(result);

  // Check if an email exists based on the query result
  if (result.length > 0) {
    console.log('email exists!');
  } else {
    console.log('email does not exist.');
  }
  return result;
}

// fetch all todos for a supervisor
async function fetchSupTodos(lawyer_id) {
  const result = await sql`
    SELECT *
    FROM todos
    WHERE l_id = ${lawyer_id}
  `;
  console.log(result);
  return result;
}

// fetch all todos for a lawyer
async function fetchTodoIds(lawyer_id) {
  const result = await sql`
    SELECT todo_id
    FROM donetodo
    WHERE l_id = ${lawyer_id}
  `;
  console.log(result);
  return result;
}

// create a todo
async function createTodo(title, description, deadline, l_id) {
  const dateObject = new Date(`${deadline}T00:00:00.000Z`);
  if (isNaN(dateObject.getTime())) {
    console.error('Invalid date format');
    return; // Exit the function if the date is invalid
  }

  // Format the date object to be in the correct format (timestamp)
  const formattedDeadline = dateObject.toISOString();
  const result = await sql`INSERT INTO todos (title, description, deadline, L_id) VALUES (${title}, ${description}, ${formattedDeadline}, ${l_id});`;
  console.log(result);
  return result;
}

// fetch a todo id
async function fetchTodoId(title, description, l_id) {
  const result = await sql`
    SELECT id
    FROM todos
    WHERE title = ${title} AND description = ${description} AND l_id = ${l_id}
  `;
  console.log(result[0]);
  return result[0].id;
}

// asssign a todo to lawyers
async function assignTodoToLawyers(todo_id, l_id) {
  const result = await sql`
    INSERT INTO donetodo (l_id, todo_id, done)
    VALUES
      (${l_id}, ${todo_id}, false)
  `;
  console.log(result);
}

// delete a todo

const openai = new OpenAI();
const app = express();
app.use(express.urlencoded({ extended: true }));
app.use(express.json());
app.use(cors());


var assistantId = process.env.assistantId;

//
// THREADS
//
// Create a thread RETURNS THREAD ID
async function createThread() {
  const emptyThread = await openai.beta.threads.create();

  console.log(emptyThread);
  return emptyThread.id;
}

// Read a thread
async function readThread(threadId) {
  const myThread = await openai.beta.threads.retrieve(
    threadId
  );

  console.log(myThread);    
}

// Delete a thread
async function deleteThread(threadId) {
  const response = await openai.beta.threads.del(threadId);

  console.log(response);
}

//
// MESSAGES
//
// Create a Message RETURNS MESSAGE ID
async function createMessage(threadId, content) {
  const threadMessages = await openai.beta.threads.messages.create(
    threadId,
    { role: "user", content: content }
  );

  console.log(threadMessages.id);
  return threadMessages.id;
}

// Read a Message RETURNS MESSAGE CONTENT
async function readMessage(threadId, msgId) {
  const message = await openai.beta.threads.messages.retrieve(
    threadId,
    msgId
  );

  console.log(message.content[0].text.value);
  return message.content[0].text.value;
}

// List Messages RETURNS AN ARRAY OF DATA LOOK INSIDE TO GET EXAMPLE
async function listMessages(threadId) {
  const threadMessages = await openai.beta.threads.messages.list(
    threadId
  );
  return threadMessages;
}

//
// RUNS
//
// Create a run RETURNS RUN ID
async function createRun(threadId) {
  const run = await openai.beta.threads.runs.create(
    threadId,
    { assistant_id: assistantId }
  );

  console.log(run.id);
  return run.id;
}

// Read a run RETURNS RUN STATUS
async function readRun(threadId, runId) {
  const run = await openai.beta.threads.runs.retrieve(
    threadId,
    runId
  );

  console.log(run.status);
  return run.status;
}

// REQUIRES ACTION FUNCTION `still needs developing`
async function submitToolOutputsToRun(threadId, runId) {
  const run = await openai.beta.threads.runs.submitToolOutputs(
    threadId,
    runId,
    {
      tool_outputs: [
        {
          tool_call_id: "call_abc123",
          output: "28C",
        },
      ],
    }
  );

  console.log(run);
}

// List runs RETURNS BIG OBJECT HAS ATTRIBUTE `data` WHICH IS AN ARRAY OF RUN OBJECTS
async function listRuns(threadId) {
  const runs = await openai.beta.threads.runs.list(
    threadId
  );

  console.log(runs.data);
  return runs.data;
}

//
// APP
//

var currentThreadId = "";
var currentRunId = "";
var currentRunStatus = "";
var currentMsgId = "";
var currentResponse = "";
var lastOutputId = "";
var lawyer;
var todos = [];
var todoIds;

// removing unncessary string from date
function cleanDate(date1) {
  let dateFromDatabase = new Date(date1);
  // Convert to string with the desired format

  let formattedDateString = dateFromDatabase.toLocaleDateString('en-US', {
    year: 'numeric',
    month: '2-digit',
    day: '2-digit',
  });
  return formattedDateString;
}

// converting deadline date to proper format
function convertDateFormat(inputDate) {
  // Split the input date into components
  var dateComponents = inputDate.split('/');

  // Create a new Date object using the components
  var formattedDate = new Date(dateComponents[2], dateComponents[0] - 1, dateComponents[1]);

  // Extract the year, month, and day from the Date object
  var year = formattedDate.getFullYear();
  var month = (formattedDate.getMonth() + 1).toString().padStart(2, '0');
  var day = formattedDate.getDate().toString().padStart(2, '0');

  // Construct the desired format
  var outputDate = year + '-' + month + '-' + day;

  return outputDate;
}



// Get Last Output ID
async function getLastId(threadId) {
  const threadMessages = await openai.beta.threads.messages.list(
    threadId
  );
  console.log(threadMessages.body.first_id);
  return threadMessages.body.first_id;
}

// Create new thread / Conversation
app.get('/new', async (req, res) => {
  currentThreadId = await createThread();

  res.send(currentThreadId);
});

// Test
app.post('/chatt', (req, res) => {
  let threadId = "";
  let msg = "";
  console.log(req.body);

  msg = req.body.msg;
  threadId = req.body.threadId;

  console.log(msg);
  console.log(threadId);
  
  res.send(JSON.stringify({
    "msg": msg,
    "threadId": threadId
  }));
});


// Chat with the assistant
app.post('/chat', async (req, res) => {
  var msg = req.body.msg;
  var threadId = req.body.threadId;
  
  console.log(msg);
  console.log(threadId);

  currentThreadId = threadId;
  
  currentMsgId = await createMessage(currentThreadId, msg);

  currentRunId = await createRun(currentThreadId, assistantId);

  currentRunStatus = await readRun(currentThreadId, currentRunId);

  while (currentRunStatus != "completed") 
    currentRunStatus = await readRun(currentThreadId, currentRunId);
  
  lastOutputId = await getLastId(currentThreadId);

  currentResponse = await readMessage(currentThreadId, lastOutputId);

  res.write(currentResponse);

  res.end();
});


// Delete a thread
app.post('/delete', async (req, res) => {
  let threadId = req.body.threadId;

  await deleteThread(threadId);

  res.send("Thread deleted");
});


app.get('/', (req, res) => {
  res.send("Hello World");
});


// register a new account
app.post('/register', async (req, res) => {
  let name = req.body.name;
  let password = req.body.password;
  let job_title = req.body.job_title;
  let type = req.body.type;
  let email = req.body.email;
  let sup_email = req.body.sup_email;
  let sup_id = null;

  // Check if any of the required fields is missing
  if (!name || !password || !job_title || !type || !email || !sup_email) {
    res.send({"word": "Missing required fields"});
  }

  if (type != "supervisor") {
    let sup_id_result = await sql`select id from lawyer where email = ${sup_email}`;
      // Check if sup_email exists or not
      if (sup_id_result.length === 0 && type != "supervisor") {
        res.send({"word": "wrong supervisor email"});
        return; // Stop execution here if supervisor email doesn't exist
      }
      sup_id = sup_id_result[0].id;
  }
  else {
    sup_id = null;
  }

  
  let emailExists = await checkEmail(email);

  if (emailExists.length > 0) {
    console.log("email already exists");
    res.send({"word": "email already exists"});
    return;
  }

  let result = await createAccount(name, password, job_title, type, email, sup_id);


  if (result.length === 0) {
    res.send({"word": "account created"});
  } else {
    res.send({"word": "account creation failed"});
  }
});

// login to an account
app.post('/login', async (req, res) => {
  let email = req.body.email;
  let password = req.body.password;

  let emailExists = await checkEmail(email);
  
  if (emailExists.length > 0) {
    let result = await login(email, password);

    if(result.length == 0) {
      res.send({"word": "wrong password"});
    }

    else {
      // res.write(JSON.stringify(result[0]));
      lawyer = result[0];

      if (lawyer.type == "supervisor") {
        // Fetching todos for supervisor
        todos = await fetchSupTodos(lawyer.id);
        
        if (todos.length > 0) {
          // Removing unnecessary string from date
          for (let i = 0; i < todos.length; i++) {
            todos[i].deadline = cleanDate(todos[i].deadline);
          }

          // Fetching done status for todos
          for(let i = 0; i < todos.length; i++) {
            let done = await sql`SELECT done FROM donetodo WHERE todo_id = ${todos[i].id}`;
            todos[i].done = done[0].done;
          }

          // Fetching junior names for todos
          for(let i = 0; i < todos.length; i++) {
            let juniors = await sql`SELECT name FROM lawyer WHERE id IN (SELECT l_id FROM donetodo WHERE todo_id = ${todos[i].id})`;
            todos[i].name = juniors[0].name;
          }

          
          res.send({
            "user": lawyer,
            "todos": todos,
            "word": "supervisor logged in successfully"
          });
        }
        else {
          res.send({
            "user": lawyer,
            "todos": "no todos",
            "word": "supervisor logged in successfully"
          });
        }
      }
      else {
        // Fetching todos for lawyer
        todoIds = await fetchTodoIds(lawyer.id);

        if (todoIds.length > 0) {
          const todosPromises = todoIds.map(async (todoId) => {
            const result = await sql`
              SELECT *
              FROM todos
              WHERE id = ${todoId.todo_id}
            `;
            return result[0]; // Assuming your query returns an array of todos
          });
        
          todos = await Promise.all(todosPromises);

          for(let i = 0; i < todos.length; i++) {
            let done = await sql`SELECT done FROM donetodo WHERE todo_id = ${todos[i].id}`;
            todos[i].done = done[0].done;
          }

          // Removing unnecessary string from date
          for (let i = 0; i < todos.length; i++) {
            todos[i].deadline = cleanDate(todos[i].deadline);
          }
          let supName = "";
          let supNameResult = await sql`SELECT name From lawyer WHERE id = ${lawyer.sup_id}`;
          supName = supNameResult[0].name; 

          for (let i = 0; i < todos.length; i++) {
            todos[i].name = supName;
          }
          // res.write(JSON.stringify(todos));
          res.send({
            "user": lawyer,
            "todos": todos,
            "word": "logged in successfully"
          });
        }
        else {
          res.send({
            "user": lawyer,
            "todos": "no todos",
            "word": "logged in successfully"
          });
        }
      }
    }
  }

  else {
    res.send({"word": "email does not exist"});
  }

});

// create a todo
app.post('/create', async (req, res) => {
  let title = req.body.title;
  let description = req.body.description;
  let deadline = convertDateFormat(req.body.deadline);
  let l_id = lawyer.id;
  let junior_id = req.body.junior_id;

  let result = await createTodo(title, description, deadline, l_id);
  let todo_id = await fetchTodoId(title, description, l_id);

  await assignTodoToLawyers(todo_id, junior_id);

  if(result.length == 0) {
    res.send({"word": "Todo created and assigned", "todo_id": todo_id});
  }
  else {
    res.send({"word": "Todo creation failed"});
  }
});

// get juniors
app.get('/juniors', async (req, res) => {
  let result = await sql`
    SELECT *
    FROM lawyer
    WHERE sup_id = ${lawyer.id}
  `;

  if (result.length > 0) {
    res.send({"user": result});
  } else {
    res.send({"word": "no juniors"});
  }
});

// get all lawyers
app.get('/lawyers', async (req, res) => {
  let result = await sql`
    SELECT *
    FROM lawyer
  `;

  if (result.length > 0) {
    res.send({"user": result});
  } else {
    res.send({"word": "no lawyers"});
  }
});

// get todos
app.get('/todos', async (req, res) => {
  let result = await sql`
    SELECT *
    FROM todos
  `;

  if (result.length > 0) {
    res.send({"todos": result});
  } else {
    res.send({"word": "no todos"});
  }
});

// get todos status
app.get('/todosstatus', async (req, res) => {
  let result = await sql`
    SELECT *
    FROM donetodo
  `;

  if (result.length > 0) {
    res.send({"todosStatus": result});
  } else {
    res.send({"word": "no todos"});
  }
});

// done lawyer
app.post('/done', async (req, res) => {
  let id = req.body.id;
  let result = await sql`
    UPDATE donetodo
    SET done = true
    WHERE todo_id = ${id} AND l_id = ${lawyer.id}
  `;

  if (result.length == 0) {
    res.send({"word": "todo marked as done"});
  } else {
    res.send({"word": "todo marking as done failed"});
  }
});

// delete a todo
app.post('/deletetodo', async (req, res) => {
  let id = req.body.id;

  let result = await sql`
    DELETE FROM todos
    WHERE id = ${id}
  `;

  if(result.length == 0) {
    res.send({"word": "todo deleted"});
  }
  else {
    res.send({"word": "todo deletion failed"});
  }
});

// search for a user name
app.post('/namesearch', async (req, res) => {

  let name = req.body.name;

  let result = await sql`
    SELECT *
    FROM lawyer
    WHERE name LIKE '%' || ${name} || '%';
  `;

  if (result.length > 0) {
    res.json(result);
  } else {
    res.send({"word": "user not found"});
  }

});

// search for a user email
app.post('/emailsearch', async (req, res) => {

  let email = req.body.email;

  let result = await sql`
    SELECT *
    FROM lawyer
    WHERE email LIKE '%' || ${email} || '%';
  `;

  if (result.length > 0) {
    res.json(result);
  } else {
    res.send({"word": "user not found"});
  }

});

app.listen(4000, () => {
  console.log('Server connected');
});
await getPgVersion();