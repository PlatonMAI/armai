-- Вычисление возраста участников

CREATE OR REPLACE FUNCTION update_participants_age()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE participants
    SET age = EXTRACT(YEAR FROM AGE(CURRENT_DATE, u.birth))
    FROM users u
    WHERE participants.competition_id = NEW.id
      AND participants.user_id = u.id;
    
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_update_participants_age
AFTER UPDATE OF status
ON competitions
FOR EACH ROW
WHEN (NEW.status = 'in_process')
EXECUTE FUNCTION update_participants_age();


-- Проставление выигравших участников в последующих армфайтах

CREATE OR REPLACE FUNCTION update_participants_after_winner()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE armfights
    SET participant_first_id = NEW.winner_id
    WHERE armfight_first_id = NEW.id;

    UPDATE armfights
    SET participant_second_id = NEW.winner_id
    WHERE armfight_second_id = NEW.id;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_update_participants
AFTER UPDATE OF winner_id
ON armfights
FOR EACH ROW
WHEN (NEW.winner_id IS NOT NULL)
EXECUTE FUNCTION update_participants_after_winner();



-- Проставление выигрышей

CREATE OR REPLACE FUNCTION increment_wins_on_winner()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE users
    SET wins_armfights = wins_armfights + 1
    WHERE id = (SELECT user_id FROM participants WHERE id = NEW.winner_id);

    UPDATE teams
    SET wins_armfights = wins_armfights + 1
    WHERE id = (SELECT team_id FROM participants WHERE id = NEW.winner_id AND team_id IS NOT NULL);

    IF NEW.is_final = true THEN
        UPDATE users
        SET wins_competitions = wins_competitions + 1
        WHERE id = (SELECT user_id FROM participants WHERE id = NEW.winner_id);

        UPDATE teams
        SET wins_competitions = wins_competitions + 1
        WHERE id = (SELECT team_id FROM participants WHERE id = NEW.winner_id AND team_id IS NOT NULL);
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_increment_wins
AFTER UPDATE OF winner_id
ON armfights
FOR EACH ROW
WHEN (NEW.winner_id IS NOT NULL)
EXECUTE FUNCTION increment_wins_on_winner();



-- Завершение соревнования

CREATE OR REPLACE FUNCTION check_and_finish_competition()
RETURNS TRIGGER AS $$
DECLARE
    all_finals_completed BOOLEAN;
BEGIN
    SELECT NOT EXISTS (
        SELECT 1
        FROM armfights
        WHERE competition_id = NEW.competition_id
          AND is_final = true
          AND winner_id IS NULL
    ) INTO all_finals_completed;

    IF all_finals_completed THEN
        UPDATE competitions
        SET status = 'finished'
        WHERE id = NEW.competition_id;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_finish_competition
AFTER UPDATE OF winner_id
ON armfights
FOR EACH ROW
WHEN (NEW.is_final = true AND NEW.winner_id IS NOT NULL)
EXECUTE FUNCTION check_and_finish_competition();
