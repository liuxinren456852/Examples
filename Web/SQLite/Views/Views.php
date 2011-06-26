SELECT
pr.Giver AS Giver,
pl2.Name AS GiverName,
pr.Receiver AS Receiver,
pl.Name AS ReceiverName
FROM Pairing pr
JOIN People pl ON pr . Receiver = pl . PersonId
JOIN People pl2 ON pr.Giver = pl2.PersonId