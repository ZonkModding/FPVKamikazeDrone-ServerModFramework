const crypto = require('crypto');

const SECRET_KEY = process.env.SECRET_KEY || 'HmLEgNuE={vPJoV:of/9[.+9tMDzpr9e!v4n.?E0Wf>!{)sWjv3aMg4kkoxA}>';
const VALID_KEYS = new Set([
    "a1b2c3d4e5f6g7h8i9j0k1l2m3n4o5p6q7r8s9t0u1v2w3x4y5z6a7b8c9d0e1f2",
    "f1e2d3c4b5a69876543210fedcba9876543210abcdef1234567890abcdef1234"
]);

module.exports = async (req, res) => {
    // 1. Получаем ключ И хэш от клиента
    const { key, hash } = req.query; 

    // 2. Эталонный хэш (вставь сюда реальный хэш своей DLL после билда!)
    const ORIGINAL_HASH = "3eac42456b879a2c4b8df5e129776aec32a5084c50d79253008100a48a191e67"; 

    // 3. Проверка ключа И хэша
    if (!key || !VALID_KEYS.has(key) || hash !== ORIGINAL_HASH) {
        return res.status(403).json({ error: 'BLOCKED' }); 
    }

    const signature = crypto.createHmac('sha256', SECRET_KEY)
                            .update(key)
                            .digest('hex');

    res.status(200).json({ signature });
};