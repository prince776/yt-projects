import { Hono } from "hono";

const app = new Hono();

const port = process.env.PORT || 3000;

const home = app.get("/", (c) => {
  const cnt = 5000;
  let result = 0;
  for (let i = 0; i < cnt; i++) {
    result += Math.floor(Math.random() * 100);
  }
  return c.json({ randomSum: result });
});

console.log(`Running at http://localhost:${port}`);

export default {
  port: process.env.PORT || 3000,
  fetch: home.fetch,
};
