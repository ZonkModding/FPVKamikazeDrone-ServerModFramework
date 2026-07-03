const fastify = require('fastify')({ logger: true });
const checkHandler = require('./api/check');

fastify.all('/api/check', async (request, reply) => {
    const req = { query: request.query };
    const res = {
        status: (code) => ({
            json: (data) => reply.code(code).send(data)
        })
    };
    await checkHandler(req, res);
});

const start = async () => {
    try {
        await fastify.listen({ port: 3000, host: '0.0.0.0' });
    } catch (err) {
        process.exit(1);
    }
};

start();