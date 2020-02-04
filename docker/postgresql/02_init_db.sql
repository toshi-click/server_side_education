-- DROP SEQUENCE training_id_seq;

CREATE SEQUENCE training_id_seq START 1;

CREATE TABLE training
(
    id             INTEGER DEFAULT nextval('training_id_seq') NOT NULL /* ID */
    , trainingName TEXT                                                /* 名前 */
    , trainingAge  SMALLINT                                            /* 年齢 */

    , PRIMARY KEY (id)
);
INSERT INTO training VALUES (1, 'test', 11) RETURNING id;
